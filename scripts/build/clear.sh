#!/bin/bash

#* project's relative path with respect to this script
PROJECT_PATH="../.."
CLEAR_DIR="$PROJECT_PATH/build"
#CLEAR_EXES=$PROJECT_PATH/*.exe

#* hide popd and pushd stdout by redefining the commands
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

#* remove dir
if [[ -d "$CLEAR_DIR" ]]; then
rm -r -f $CLEAR_DIR

if [[ $? -eq 0 ]]; then
   echo "Removed $CLEAR_DIR"
fi
fi

#* remove exe
#rm -f $CLEAR_EXES
#if [[ $? -eq 0 ]]; then
#   echo "Removed $CLEAR_EXES"
#fi

echo "$0 done."
