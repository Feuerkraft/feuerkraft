{
  description = "A Tank Battle Game";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
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
             pname = "feuerkraft";
             version = "0.1.1";

             src = ./.;

             nativeBuildInputs = with pkgs; [
               cmake
               pkg-config
             ];

             buildInputs = with pkgs; [
               swig
               guile_3_0
               libGLU
               libGL
             ] ++ [
               clanlib.packages.${system}.default
             ];
           };
        };
       }
    );
}
