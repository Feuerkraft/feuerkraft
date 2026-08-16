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
      in {
        packages = rec {
          default = feuerkraft;

          feuerkraft = pkgs.stdenv.mkDerivation {
            pname = "feuerkraft";
            version = "0.2.0";

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
