#!/bin/bash

#* project's relative path with respect to this script
PROJECT_PATH=../..

#* C/CXX compiler absolute path for MSYS2 on Windows
C_COMPILER_PATH="/c/msys64/mingw64/bin/x86_64-w64-mingw32-gcc.exe"
CXX_COMPILER_PATH="/c/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe"

#* hide popd and pushd stdout by defining new commands
popds () {	
	command popd "$@" > /dev/null	
}
pushds () {	
	command pushd "$@" > /dev/null	
}
#* change the cwd to the script dir temporarily until the script exits for any reason
#* (use BASH_SOURCE if it exists, otherwise fall back to $0)
trap popds EXIT
pushds "$(dirname ${BASH_SOURCE[0]:-$0})"

#* get current platform
UNAME=$(uname)

if [[ $UNAME == "Linux" ]] ; then
	cmake -S $PROJECT_PATH/ -B $PROJECT_PATH/build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
elif [[ $UNAME == "MSYS"* ]] ; then
	cmake -S $PROJECT_PATH/ -B $PROJECT_PATH/build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 --no-warn-unused-cli -DCMAKE_C_COMPILER:FILEPATH=$C_COMPILER_PATH -DCMAKE_CXX_COMPILER:FILEPATH=$CXX_COMPILER_PATH -G "MinGW Makefiles"
fi

echo "$0 done."
