#!/bin/bash

# params
CLANG_FORMAT_VERSION=5.0
SOURCE_REGEXP="/(src|tests)/.+\.(h|c)pp"

# check clang-format
CLANG_FORMAT=clang-format-$CLANG_FORMAT_VERSION
if ! [ -x `command -v $CLANG_FORMAT || echo ERROR` ]; then
  CLANG_FORMAT=clang-format
  if [ `$CLANG_FORMAT --version | grep -F "version $CLANG_FORMAT_VERSION" | wc -l` -ne 1 ]; then
    echo "Error: clang-format must be version $CLANG_FORMAT_VERSION" >&2
    exit 1
  fi
fi

cd $(dirname "$0")/../

case $1 in
  ''|--cached) # only changed
  CACHED=''
  if [ "$1" = "--cached" ]; then
	  CACHED='--cached'
  fi
  FILES=$(git diff HEAD $CACHED --name-only --diff-filter=ACMR)
  echo "$FILES" | \
  grep -E "$SOURCE_REGEXP$" | grep -vE "^(third_party|build)/" | \
  xargs -t -r $CLANG_FORMAT -i

  # For return code
  if [ "$1" = "--cached" ]; then
    ! git diff $FILES | grep -q .
  fi
  ;;
  -a|--all) # all sources
  find . -type f -regextype posix-egrep -regex ".*$SOURCE_REGEXP" -not -path "./third_party/*" -not -path "./build/*" -exec \
  $CLANG_FORMAT -i {} +
  ;;
  *) # error
  echo "Error: $0 [-a|--all]" >&2
  exit 1
  ;;
esac
