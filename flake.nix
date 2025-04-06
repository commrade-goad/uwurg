{
    description = "UwUrg game.";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
        flake-utils.url = "github:numtide/flake-utils";
    };

    outputs = { self, nixpkgs, flake-utils }:
        flake-utils.lib.eachDefaultSystem (system:
            let
                pkgs = nixpkgs.legacyPackages.${system};
            in
                {
                packages.default = pkgs.stdenv.mkDerivation {
                    pname = "uwurg";
                    version = "0.0.3";
                    src = self;

                    nativeBuildInputs = with pkgs; [
                        cmake
                        pkg-config
                        gcc
                    ];

                    buildInputs = with pkgs; [
                        glib
                        libGL
                        xorg.libX11
                        xorg.libXcursor
                        xorg.libXrandr
                        xorg.libXinerama
                        xorg.libXi
                    ];

                    meta = {
                        description = "UwUrg game.";
                        homepage = "https://github.com/commrade-goad/uwurg";
                    };
                };
                devShells.default = pkgs.mkShell {
                    buildInputs = with pkgs; [
                        cmake
                        pkg-config
                        gcc
                        gdb
                        gdbgui

                        glib
                        libGL
                        xorg.libX11
                        xorg.libXcursor
                        xorg.libXrandr
                        xorg.libXinerama
                        xorg.libXi
                    ];
                };
            }
        );
}
