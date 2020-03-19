#!/bin/bash

mkdir -p tmp

AUTOCORRECT=0
while getopts ":a" opt; do
  case $opt in
    a )
      AUTOCORRECT=1
      shift
      ;;
    \?)
      echo "Error: invalid flag $opt"
      exit 1
      ;;
  esac
done

if [ $# -ne 0 ]; then
  files="$@"
else
  files=$(git ls-files -c -m -o --exclude-standard -- '*.cc' '*.hh')
fi

ERRS=0

echo "Check C++ format:"
for file in $files; do
  clang-format -- "$file" > tmp/format
  if [ ! -f "$file" ]; then
    echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(file not found)\033[1;37m\n"
    ERRS=$((ERRS+1))
    continue
  fi
  if ! diff -u "$file" tmp/format > tmp/format.diff; then
    echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(format)\033[1;37m\n"
    cat tmp/format.diff | sed "s/^/        /g" | tail -n +3
    echo -e "\n"
    ERRS=$((ERRS+1))

    if [ $AUTOCORRECT -eq 1 ]; then
      mv tmp/format "$file";
      echo -e "\tAutocorrect applied!"
    fi

    continue
  fi

  echo -e " * [\033[1;32mOK\033[0;37m] $file"
done

if [ $ERRS -ne 0 ]; then
    echo -e "\nThere are formatting errors! Run format_cxx.sh with \`-a\`.\n"
    exit 1
fi

rm -rf tmp

echo -e "\nNo error. Good job!\n"
exit 0
