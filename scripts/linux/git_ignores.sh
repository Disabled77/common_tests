#!/bin/sh
#Script set up .gitignore

usage() {
    echo "Set up gitignore. Run scripts from working tree to:"
    echo "ignore system files in working tree"
    echo "ignore everything in build"
    echo "ignore everything in bin"
    echo "ignore everything in .idea"
}

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
   usage
   exit 0
fi

echo "Setting up gitignores"

if [ ! -e .gitignore ]; then
    touch .gitignore
    cat >> .gitignore << EOF
    *.creator
    *.config
    *.user
    *.files
    *.includes
EOF
fi

ignore_dir(){
   if [ -d $1 ] && [ ! -e $1/.gitignore ]; then
      touch -a $1/.gitignore
      echo '*.*' >> $1/.gitignore
   fi
}

ignore_dir "build"
ignore_dir "bin"
ignore_dir ".idea"






