#!/bin/bash

TESTS=0
ERRS=0

run_test() {
    cmd=../rbs2rbi
    file=$1
    out_dir=$2

    test_name=$(basename "${file%.*}")
    test_out="$out_dir/$test_name.rbi"
    test_err="$out_dir/$test_name.err"

    TESTS=$((TESTS + 1))

    if ! "$cmd" "$file" > "$test_out" 2> "$test_err"; then
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(command failed see $test_err)\033[1;37m"
        ERRS=$((ERRS+1))
        return 1
    fi

    if [ ! -f "$test_out" ]; then
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(nothing produced)\033[1;37m"
        ERRS=$((ERRS+1))
        return 2
    fi

    echo -e " * [\033[1;32mOK\033[0;37m] $file"
    return 0
}

if [ $# -ne 1 ]; then
    echo "Error: no arguments supplied."
    echo "Usage: test_stdlib.sh <rbs_dir>"
    exit 1
fi

# Compile RBIS

tests_dir=$1
out_dir="sorbet/stdlib"
rm -rf "$out_dir"
mkdir -p "$out_dir"

echo "Compiling RBI files from '$1':"
for file in $(find "$tests_dir" -name "*.rbs" | sort); do
    run_test  "$file" "$out_dir"
done

if [ $ERRS -ne 0 ]; then
    echo -e "\nCompiled $TESTS RBS files, $ERRS errors! (see 'sorbet/stdlib/*.err' for investigation)\n"
    exit 1
fi

# TODO when ready
# Test with Sorbet
echo -e "\nTesting with sorbet:"
cd sorbet || exit 1
if ! bundle exec srb tc --no-stdlib --stop-after namer; then
    echo -e " * [\033[1;31mKO\033[0;37m] bundle exec srb tc \033[1;90m(Sorbet produced errors)\033[1;37m"
    ERRS=$((ERRS+1))
    exit 2
fi

# rm -rf out
echo -e " * [\033[1;32mOK\033[0;37m] bundle exec srb tc"
echo -e "\nRan $TESTS tests without error. Good job!\n"
