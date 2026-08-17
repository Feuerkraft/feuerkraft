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
      in {
        packages = rec {
          default = feuerkraft;

          feuerkraft = pkgs.stdenv.mkDerivation {
            pname = "feuerkraft";
            inherit version;

            src = ./.;

            nativeBuildInputs = with pkgs; [
              cmake
              pkg-config
              swig
            ];

            buildInputs = with pkgs; [
              guile_3_0
              SDL2
              SDL2_image
              SDL2_mixer
            ];

            # Pass the full version (with git info when present) into CMake
            # so FEUERKRAFT_VERSION / PACKAGE_STRING match the Nix package.
            cmakeFlags = [
              "-DPROJECT_VERSION_FULL=${version}"
            ];
          };
        };

        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            pkg-config
            swig
            guile_3_0
            SDL2
            SDL2_image
            SDL2_mixer
          ];
        };
      }
    );
}
