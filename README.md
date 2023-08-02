# C++ Project Template
This is my C++ project template. I frequently need reference trajectories to test, so this template alse uses reference data, in this instance it is generated using MATLAB.

# How to configure, compile and test with CMake
Install the build tools if you need to:
```bash
sudo apt-get update
sudo apt-get install cmake
sudo apt-get install build-essential
sudo apt-get install libeigen3-dev
```

# How to compile on Windows using VS Code and MSYS2
1. Install MSYS2, and add to path.
2. Install mingw-w64 toolchain using MSYS2, ```pacman -S --needed base-devel mingw-w64-x86_64-toolchain```.
3. Make sure eigen is installed

Use the provided scripts or the VS Code tasks to configure, build and test:
```bash
./scripts/build/clear.sh
./scripts/build/configure.sh
./scripts/build/build.sh
./scripts/build/test.sh
```
