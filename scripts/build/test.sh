#!/bin/bash

#* project's relative path with respect to this script
PROJECT_PATH=../..

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

ctest --test-dir $PROJECT_PATH/build -t test

echo "$0 done."
