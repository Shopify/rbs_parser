#!/bin/bash


echo "Check specs are up-to-date:"

mkdir -p out
src=specs/README.src
org=specs/README.md
out=out/README.md

specs/build.sh "./rbs2rbi" "$src" > $out
if [ ! -f "$out" ]; then
    echo -e " * [\033[1;31mKO\033[0;37m] Error generating specs!"
    exit 1
fi

if ! diff -u "$out" "$org" > out/README.diff; then
    echo -e " * [\033[1;31mKO\033[0;37m] Specs not up-do-date!"
    cat out/README.diff | sed "s/^/        /g" | tail -n +3
    exit 1
fi

echo -e " * [\033[1;32mOK\033[0;37m] Specs up-do-date!"
rm -rf out
exit 0
