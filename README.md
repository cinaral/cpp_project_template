# Template C++ Project
This is my personal C++ project template.

# How to compile and test with CMake
```
cmake -S . -B build
cmake --build build
cmake --build build -t test
```

# How to compile and test with VS Code and CMake Tools on Windows
1. Install MSYS2 and add to path.
2. Install mingw-w64 toolchain via ```pacman -S --needed base-devel mingw-w64-x86_64-toolchain``` using MSYS2.
3. Install "C/C++ extension for VS Code" and "CMake Tools" VS Code extensions.