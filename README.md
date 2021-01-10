![](example.gif)
# Boids-Swarm-DLL
A DLL which runs a Boids Swarm simulation on GPU using Libtorch, designed to work with `Unreal Engine`.

## Requirements:
- CMake
- Visual Studio
- LibTorch 1.7

## Project Setup
- Clone this repo: `git clone https://github.com/NeuralVFX/boids-swarm-dll.git`
- Open `boids.cpp` and replace the `"boids.ptc"` path to match the path on your system
- Open `build/CMakeLists.txt` and replace the directort for `Torch_DIR`
- Run these commands to build the project(replace `DCMAKE_PREFIX_PATH` with your libtorch install directory):
```
cmake ./build -DCMAKE_PREFIX_PATH=C:\libtorch -DCMAKE_GENERATOR_PLATFORM=x64  ..
cmake --build . --config Release
```
- This should generate a Visual Studio Project and a file called `Release/boids.dll`
- Copy this file wherever you need!

