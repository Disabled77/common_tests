#!/bin/sh
#Script build the project

usage() {
    echo "usage: build.sh ['debug'] | ['release'] \n"
    echo "Options:"
    echo "  build the project in debug/release type"
}


if [ $# = 0 ] || [ "$1" = "debug" ]; then
   BUILD_TYPE=debug_x64
elif [ "$1" = "release" ]; then
   BUILD_TYPE=release_x64
elif [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
   usage
   exit 0
fi

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../ ../
cd ..


