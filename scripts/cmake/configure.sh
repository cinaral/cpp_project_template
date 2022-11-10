#!/bin/bash

#*  change the cwd to the script dir temporarily, and hide pushd popd output
pushd () { 
	command pushd "$@" > /dev/null 
}
popd () { 
	command popd "$@" > /dev/null 
}
pushd "$(dirname ${BASH_SOURCE:0})"
trap popd EXIT

#* specify the C/CXX compiler path for MSYS2 on Windows
C_COMPILER_PATH="/c/msys64/mingw64/bin/x86_64-w64-mingw32-gcc.exe"
CXX_COMPILER_PATH="/c/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe"

UNAME=$(uname)

if [[ $UNAME == "Linux" ]] ; then
	cmake -S ../../ -B ../../build
elif [[ $UNAME == "MSYS"* ]] ; then
	cmake -S ../../ -B ../../build --no-warn-unused-cli -DCMAKE_C_COMPILER:FILEPATH=$C_COMPILER_PATH -DCMAKE_CXX_COMPILER:FILEPATH=$CXX_COMPILER_PATH -G "MinGW Makefiles"
fi

echo "$0 done."
