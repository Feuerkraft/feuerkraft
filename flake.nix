{
  description = "A Tank Battle Game";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    clanlib.url = "github:grumbel/clanlib-1.0";
    clanlib.inputs.nixpkgs.follows = "nixpkgs";
    clanlib.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, clanlib }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
       in {
         packages = rec {
           default = feuerkraft;

           feuerkraft = pkgs.stdenv.mkDerivation {
             name = "feuerkraft";

             src = nixpkgs.lib.cleanSource ./.;

             nativeBuildInputs = [
               pkgs.cmake
               pkgs.pkgconfig
             ];

             buildInputs = [
               clanlib.packages.${system}.default

               pkgs.swig
               pkgs.guile_3_0
               pkgs.mesa
               pkgs.libGLU
               pkgs.libGL
             ];
           };
        };
       }
    );
}
