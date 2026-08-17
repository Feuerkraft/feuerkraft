{
  description = "A Tank Battle Game";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        lib = pkgs.lib;
        versionBase = lib.strings.removeSuffix "\n" (builtins.readFile ./VERSION);
        # Append .revCount+g<shortRev> only for development versions.
        version =
          if lib.strings.hasInfix "-dev" versionBase then
            let
              gitRev = "${self.shortRev or self.dirtyShortRev or "dirty"}";
              revCount = toString (self.revCount or 0);
            in
              "${versionBase}.${revCount}+g${gitRev}"
          else
            versionBase;

        # s7 is a large single-file C interpreter. Build it as its own
        # derivation so feuerkraft rebuilds do not recompile s7.c.
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

          meta = with lib; {
            description = "s7 Scheme interpreter (static library)";
            homepage = "https://ccrma.stanford.edu/software/snd/snd/s7.html";
            license = licenses.bsd0; # informal BSD-style; see upstream
          };
        };
      in {
        packages = rec {
          default = feuerkraft;
          inherit s7;

          feuerkraft = pkgs.stdenv.mkDerivation {
            pname = "feuerkraft";
            inherit version;

            src = ./.;

            nativeBuildInputs = with pkgs; [
              cmake
              pkg-config
            ];

            buildInputs = with pkgs; [
              SDL2
              SDL2_image
              SDL2_mixer
              s7
            ];

            # Pass the full version (with git info when present) into CMake
            # so FEUERKRAFT_VERSION / PACKAGE_STRING match the Nix package.
            # S7_ROOT points at the separate s7 derivation.
            cmakeFlags = [
              "-DPROJECT_VERSION_FULL=${version}"
              "-DS7_ROOT=${s7}"
            ];
          };
        };

        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            pkg-config
            SDL2
            SDL2_image
            SDL2_mixer
            s7
          ];

          # So out-of-tree cmake builds in the shell pick up the Nix s7.
          shellHook = ''
            export S7_ROOT="${s7}"
            cmakeFlagsArray+=("-DS7_ROOT=${s7}")
          '';
        };
      }
    );
}
