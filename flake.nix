{
  description = "Feuerkraft - A Tank Battle Game";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";

    # Official MinGW SDL2 packages (Windows cross), same as SuperTux/Pingus.
    SDL2-win32.url = "github:grumnix/SDL2-win32";
    SDL2-win32.inputs.nixpkgs.follows = "nixpkgs";
    SDL2_image-win32.url = "github:grumnix/SDL2_image-win32";
    SDL2_image-win32.inputs.nixpkgs.follows = "nixpkgs";

    SDL2_mixer-win32-x64 = {
      url = "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-2.8.1-win32-x64.zip";
      flake = false;
    };
    SDL2_mixer-win32-x86 = {
      url = "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-2.8.1-win32-x86.zip";
      flake = false;
    };
    sdl2-mixer-mingw-devel = {
      url = "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-devel-2.8.1-mingw.tar.gz";
      flake = false;
    };

    # SDL2 sources for Android / wasm library builds (mk/* scripts).
    sdl2-src = {
      url = "https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-2.30.9.tar.gz";
      flake = false;
    };
    sdl2-image-src = {
      url = "https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.tar.gz";
      flake = false;
    };
    sdl2-mixer-src = {
      url = "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-2.8.1.tar.gz";
      flake = false;
    };
    libxmp-src = {
      url = "https://github.com/libxmp/libxmp/releases/download/libxmp-4.6.0/libxmp-4.6.0.tar.gz";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, flake-utils
            , SDL2-win32, SDL2_image-win32
            , SDL2_mixer-win32-x64, SDL2_mixer-win32-x86, sdl2-mixer-mingw-devel
            , sdl2-src, sdl2-image-src, sdl2-mixer-src, libxmp-src }:
    flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-linux" ] (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        lib = pkgs.lib;
        versionBase = lib.strings.removeSuffix "\n" (builtins.readFile ./VERSION);
        version =
          if lib.strings.hasInfix "-dev" versionBase then
            let
              gitRev = "${self.shortRev or self.dirtyShortRev or "dirty"}";
              revCount = toString (self.revCount or 0);
            in "${versionBase}.${revCount}+g${gitRev}"
          else
            versionBase;
        gitRev = "${self.shortRev or self.dirtyShortRev or "dirty"}";
        gitDate = self.lastModifiedDate or "19700101";

        # ---- s7 as separate derivation (fast feuerkraft rebuilds) ----
        s7 = pkgs.stdenv.mkDerivation {
          pname = "s7";
          version = "11.9";
          src = ./external/s7;
          dontConfigure = true;
          buildPhase = ''
            runHook preBuild
            $CC -c -O2 -std=c11 -fPIC s7.c -o s7.o
            $AR rcs libs7.a s7.o
            runHook postBuild
          '';
          installPhase = ''
            runHook preInstall
            mkdir -p $out/lib $out/include
            install -m644 libs7.a $out/lib/libs7.a
            install -m644 s7.h $out/include/s7.h
            runHook postInstall
          '';
        };

        # ---- Desktop package ----
        feuerkraft = pkgs.stdenv.mkDerivation {
          pname = "feuerkraft";
          inherit version;
          src = ./.;
          nativeBuildInputs = with pkgs; [ cmake pkg-config ];
          buildInputs = with pkgs; [ SDL2 SDL2_image SDL2_mixer s7 ];
          cmakeFlags = [
            "-DPROJECT_VERSION_FULL=${version}"
            "-DS7_ROOT=${s7}"
          ];
        };

        # ---- WASM (mk/wasm + nix/wasm.nix, from SuperTux/Pingus) ----
        wasm = import ./nix/wasm.nix {
          inherit pkgs;
          sdlSrc = sdl2-src;
          sdlVersion = "2.30.9";
          sdlImageSrc = sdl2-image-src;
          sdlMixerSrc = sdl2-mixer-src;
          libxmpSrc = libxmp-src;
        };
        wasmDataDir = if builtins.pathExists ./data then ./data else null;

        # ---- Android (unfree SDK; license accepted here like SuperTux/Pingus) ----
        androidPkgs = import nixpkgs {
          system = pkgs.stdenv.hostPlatform.system;
          config.allowUnfree = true;
          config.android_sdk.accept_license = true;
        };
        buildToolsVersion = "30.0.3";
        packagePlatform = "22";
        compilePlatform = "33";
        ndkVersion = "23.1.7779620";
        targetAbis = [ "armeabi-v7a" "arm64-v8a" ];
        androidSdk = (androidPkgs.androidenv.composeAndroidPackages {
          platformVersions = [ packagePlatform compilePlatform ];
          buildToolsVersions = [ buildToolsVersion ];
          includeNDK = true;
          inherit ndkVersion;
          includeEmulator = false;
          includeSources = false;
        }).androidsdk;
        android = import ./nix/android.nix {
          pkgs = androidPkgs;
          sdlSrc = sdl2-src;
          sdlVersion = "2.30.9";
          sdlMixerSrc = sdl2-mixer-src;
          sdlMixerVersion = "2.8.1";
          libxmpSrc = libxmp-src;
          inherit androidSdk buildToolsVersion packagePlatform compilePlatform targetAbis;
        };
        androidApkName = "feuerkraft-${gitDate}-${gitRev}.apk";
        stbImageH = pkgs.fetchurl {
          url = "https://raw.githubusercontent.com/nothings/stb/2c980bb59875b0d32144a71867fbdebb2f77cd20/stb_image.h";
          hash = "sha256-WUwv411JSItDgtv67I+YNm3vyoGdkWrJW+zz519CALM=";
        };

        # ---- R36S / ArkOS ----
        r36s = import ./nix/r36s.nix {
          inherit (pkgs) lib stdenv stdenvNoCC fetchurl cmake pkg-config writeShellScript zip;
          pkgsCross = pkgs.pkgsCross;
        };
        feuerkraftR36s = r36s.mkFeuerkraftR36s {
          src = lib.cleanSource ./.;
          inherit version;
          pname = "feuerkraft-r36s";
        };
        feuerkraftR36sPortMaster = r36s.mkFeuerkraftR36sPortMaster {
          r36sPkg = feuerkraftR36s;
          inherit version;
          pname = "feuerkraft-r36s-portmaster";
        };

        # ---- Windows cross (MinGW) ----
        mkSdl2MixerWin = winSystem:
          let
            triplet =
              if winSystem == "x86_64-windows" then "x86_64-w64-mingw32"
              else if winSystem == "i686-windows" then "i686-w64-mingw32"
              else throw "unknown winSystem ${winSystem}";
          in
          pkgs.stdenv.mkDerivation {
            pname = "SDL2_mixer-mingw-${winSystem}";
            version = "2.8.1";
            src = sdl2-mixer-mingw-devel;
            dontBuild = true;
            installPhase = ''
              mkdir -p $out
              cp -a ${triplet}/. $out/
              # optional runtime DLL
              cp -v ${if winSystem == "x86_64-windows" then SDL2_mixer-win32-x64 else SDL2_mixer-win32-x86}/SDL2_mixer.dll $out/bin/ 2>/dev/null || true
            '';
          };

        mkWinCross = { crossPkgs, winSystem, pname }:
          let
            sdl2Win = SDL2-win32.packages.${winSystem}.default;
            sdl2ImageWin = SDL2_image-win32.packages.${winSystem}.default;
            sdl2MixerWin = mkSdl2MixerWin winSystem;
          in
          crossPkgs.stdenv.mkDerivation {
            inherit pname;
            version = version;
            src = ./.;
            nativeBuildInputs = [ crossPkgs.cmake pkgs.pkg-config ];
            buildInputs = [ sdl2Win sdl2ImageWin sdl2MixerWin ];
            cmakeFlags = [
              "-DPROJECT_VERSION_FULL=${version}"
              # Build vendored s7 with the MinGW toolchain
            ];
            postInstall = ''
              mkdir -p $out/bin
              # Stage SDL DLLs next to the exe for a flat portable tree
              find ${sdl2Win} ${sdl2ImageWin} ${sdl2MixerWin} -iname "*.dll" -exec cp -v {} $out/bin/ \; || true
              if [ -d data ]; then cp -a data $out/bin/data; fi
            '';
          };

      in {
        packages = rec {
          default = feuerkraft;
          inherit s7 feuerkraft;

          # WASM
          wasm-sdl2 = wasm.sdl2WasmLibs;
          wasm-sdl-libs = wasm.sdlWasmLibs;
          wasm-zlib-libs = wasm.zlibWasmLibs;
          feuerkraft-wasm = wasm.mkApp {
            appName = "feuerkraft";
            srcDir = ./.;
            dataDir = wasmDataDir;
            enableSound = true;
            enableGles2 = false; # SDL2 renderer, not custom GLES2
            enableAsyncify = false;
            versionFull = version;
            gitRev = gitRev;
            sourceUrl = "https://github.com/feuerkraft/feuerkraft";
          };

          # Android APK
          feuerkraft-android = android.mkApk {
            appName = "feuerkraft";
            appDir = ./mk/android/app;
            outApkName = androidApkName;
            keystore = ./mk/android/keystore/debug.keystore;
            gameSrcDir = ./src;
            gameRootDir = ./.;
            gameDataDir = ./data;
            sdl2ImageSrc = sdl2-image-src;
            stbImageH = stbImageH;
            gameVersion = version;
          };

          # R36S / PortMaster (ArkOS aarch64)
          arkos-sysroot = r36s.arkosSysroot;
          feuerkraft-r36s = feuerkraftR36s;
          feuerkraft-r36s-portmaster = feuerkraftR36sPortMaster;
          feuerkraft-r36s-portmaster-zip = r36s.mkFeuerkraftR36sPortMasterZip {
            portMasterPkg = feuerkraftR36sPortMaster;
            inherit version;
            pname = "feuerkraft-r36s-portmaster-zip";
          };

          # Windows cross from Linux
          feuerkraft-win64 = mkWinCross {
            crossPkgs = pkgs.pkgsCross.mingwW64;
            winSystem = "x86_64-windows";
            pname = "feuerkraft-win64";
          };
          feuerkraft-win32 = mkWinCross {
            crossPkgs = pkgs.pkgsCross.mingw32;
            winSystem = "i686-windows";
            pname = "feuerkraft-win32";
          };
        };

        apps = {
          feuerkraft-wasm = wasm.mkOpenBrowserApp {
            pkg = self.packages.${system}.feuerkraft-wasm;
            appName = "feuerkraft";
          };
          install-android-feuerkraft = android.mkInstallApp {
            pkg = self.packages.${system}.feuerkraft-android;
            apkFileName = androidApkName;
          };
        };

        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake pkg-config
            SDL2 SDL2_image SDL2_mixer
            s7
            emscripten
          ];
          shellHook = ''
            export S7_ROOT="${s7}"
            echo "Feuerkraft dev shell — S7_ROOT=$S7_ROOT"
            echo "Targets: nix build .#feuerkraft .#feuerkraft-wasm .#feuerkraft-win64"
          '';
        };
      }
    );
}
