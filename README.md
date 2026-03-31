# C++ Project Template
This is my C++ project template, which uses reference data (e.g. generated using MATLAB) for testing.

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

# License
```
Copyright 2026 Cinar A. L.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 of the License.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
```