{
  description = "A Tank Battle Game";

  inputs = {
    nixpkgs.url = "github:grumbel/nixpkgs/fix-guile-3.0";
    # nixpkgs.url = "github:NixOS/nixpkgs/nixos-21.11";
    flake-utils.url = "github:numtide/flake-utils";

    clanlib.url = "gitlab:grumbel/clanlib-1.0";
    clanlib.inputs.nixpkgs.follows = "nixpkgs";
    clanlib.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, clanlib }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
       in rec {
         packages = flake-utils.lib.flattenTree rec {
           feuerkraft = pkgs.stdenv.mkDerivation {
             name = "feuerkraft";
             src = nixpkgs.lib.cleanSource ./.;
             cmakeFlags = [];
             nativeBuildInputs = [
               pkgs.cmake
               pkgs.ninja
               pkgs.gcc
               pkgs.pkgconfig
             ];
             buildInputs = [
               clanlib.defaultPackage.${system}

               pkgs.swig
               pkgs.guile_3_0
               pkgs.mesa
               pkgs.libGLU
               pkgs.libGL
             ];
           };
        };
        defaultPackage = packages.feuerkraft;
      });
}
