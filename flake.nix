{
  description = "Nix";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-22.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: flake-utils.lib.eachDefaultSystem (system: 
    let
      # system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
      };
    in
    {
      # https://github.com/NixOS/nixpkgs/blob/master/pkgs/stdenv/generic/make-derivation.nix
      packages.default = pkgs.stdenv.mkDerivation {
        name = "app";
        src = ./.;

        nativeBuildInputs = with pkgs; [
          clang
          # CMake is configured behind the scene
          cmake
        ];

        builtInputs = with pkgs; [
          glfw
          glew
          glm
          stb
          imgui
        ];

        # shellHook = ''
        #   export CMAKE_MODULE_PATH="${pkgs.glfw}/lib"
        # '';

        # phases = [
        #   "buildPhase"
        #   "installPhase"
        # ];

        buildPhase = "make -j $NIX_BUILD_CORES";

        installPhase = ''
          mkdir -p $out/bin
          cp $src/app $out/bin
        '';
      };
    }
  );
}
