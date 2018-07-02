#!/bin/sh
#Script build the project

usage() {
    echo "usage: build.sh ['debug'] | ['release'] \n"
    echo "Options:"
    echo "  build the project in debug/release type"
}


if [ $# = 0 ] || [ "$1" = "debug" ]; then
   BUILD_TYPE=debug_x64
elif [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
   BUILD_TYPE=release_x64
fi

cd Build; ./premake5 gmake; cd ..
cd project_gmake; make config=$BUILD_TYPE; cd ..


