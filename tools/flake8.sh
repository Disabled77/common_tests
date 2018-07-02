#!/bin/sh
#Script check python codestyle for the last commit or selected path

usage() {
    echo "usage: flake8.sh --smart | <path1> [path2 ...] \n"
    echo "Options:"
    echo "  --smart  check only git modified files from the last commit"
    echo "  path1 [path2 ...] check selected file(s) or directory(ies)"
}


#check input args
if [ $# = 0 ]; then
   echo >&2 "Error: no arguments"
   usage
   exit 1
elif [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
   usage
   exit 0
fi


#prepare files to inspect
if [ "$1" = "--smart" ]; then
    INPUT=$(git diff HEAD --name-only --diff-filter d | grep -E '\.py$')
    if [ "$INPUT" = "" ]; then
        exit 0
    fi
else
    INPUT="$@"
fi


#inspect files
FLAKE8=${FLAKE8:-$(which flake8)}
FLAKE8=${FLAKE8:-python -mflake8}

CONFIG_PATH="$(dirname "$0")/../.flake8"

$FLAKE8 --config=${CONFIG_PATH} --show-source $INPUT
