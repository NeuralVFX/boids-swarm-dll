![](example.gif)
# Boids-Swarm-DLL
A DLL which runs a Boids Swarm simulation on GPU using Libtorch, designed to work with `Unreal Engine`.

## About
This is one of two repositories which are required to build this project:
- [unreal-boids-swarm-plugin](https://github.com/NeuralVFX/unreal-boids-swarm-plugin)
- [boids-swarm-dll](https://github.com/NeuralVFX/boids-swarm-dll/) - You are here.

## Extra Info
- The actual Boids Algorithm is implemented in Pytorch
- It's implemented in 3d, with both goal targeting and avoidance
- The model has been JIT traced and can be run by LibTorch on GPU

## Requirements:
- CMake
- Visual Studio
- LibTorch 1.7
- PyTorch 1.7 (Required Only to Re-Export Model)

## Project Setup
- Clone this repo: `git clone https://github.com/NeuralVFX/boids-swarm-dll.git`
- Open `boids.cpp` and replace the `"boids.ptc"` path to match the path on your system
- Open `build/CMakeLists.txt` and replace the path for `Torch_DIR`
- Run these commands to build the project(replace `DCMAKE_PREFIX_PATH` with your libtorch install directory):
```
cmake ./build -DCMAKE_PREFIX_PATH=C:\libtorch -DCMAKE_GENERATOR_PLATFORM=x64  ..
cmake --build . --config Release
```
- This should generate a Visual Studio Project and a file called `Release/boids.dll`
- Copy this file wherever you need!

## PyTorch/Jit Trace
- If you are interested to modify or re-export the Boids model, Run this [Jupyter Notebook](BoidsJitExport.ipynb).

