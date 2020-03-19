#!/bin/bash

TESTS=0
ERRS=0

run_tests() {
    cmd=$1
    tests_dir=$2
    res_dir=$3

    out_dir="out/$(basename "$1")"
    mkdir -p "$out_dir"

    for file in $(find "$tests_dir" -name "*.rbs" | sort); do
        run_test "$cmd" "$file" "$res_dir" "$out_dir"
    done
}

run_test() {
    cmd=$1
    file=$2
    res_dir=$3
    out_dir=$4

    test_name=$(basename "${file%.*}")
    test_res_ok="$res_dir/$test_name.res"
    test_res_ko="$res_dir/$test_name.err"
    test_out="$out_dir/$test_name.out"
    test_err="$out_dir/$test_name.err"

    TESTS=$((TESTS + 1))

    if ! "$cmd" "$file" > "$test_out" 2> "$test_err" ; then
        if [ ! -f "$test_res_ko" ]; then
            echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(unexpected errors: $test_err)\033[1;37m"
            cat "$test_err"
            ERRS=$((ERRS+1))
            return 1
        fi
        if ! diff -u "$test_err" "$test_res_ko" > /dev/null; then
            echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(diff -u $test_err $test_res_ko)\033[1;37m"
            ERRS=$((ERRS+1))
            return 1
        fi
        # Expected error is ok
        echo -e " * [\033[1;32mOK\033[0;37m] $file"
        return 0
    fi

    if [ ! -f "$test_out" ]; then
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(nothing produced)\033[1;37m"
        ERRS=$((ERRS+1))
        return 1
    fi

    if [ ! -f "$test_res_ok" ]; then
        # No res file for this test, we emit a warning
        echo -e " * [\033[1;33m??\033[0;37m] $file \033[1;90m(no res file $test_out $test_res_ok)\033[1;37m"
        return 0
    fi

    if ! diff -u "$test_out" "$test_res_ok" > /dev/null; then
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(diff -u $test_out $test_res_ok)\033[1;37m"
        ERRS=$((ERRS+1))
        return 1
    fi

    if [ -s "$test_err" ] && [ ! -f "$test_res_ko" ]; then
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(unexpected warnings: $test_err)\033[1;37m"
        ERRS=$((ERRS+1))
        return 1
    fi

    if [ ! -s "$test_err" ] && [ -f "$test_res_ko" ]; then
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(no warning produced while expected in $test_res_ko)\033[1;37m"
        ERRS=$((ERRS+1))
        return 1
    fi

    if [ -s "$test_err" ] && ! diff -u "$test_err" "$test_res_ko" > /dev/null; then
        # Warnings mismatch
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(diff -u $test_err $test_res_ko)\033[1;37m"
        ERRS=$((ERRS+1))
        return 1
    fi

    echo -e " * [\033[1;32mOK\033[0;37m] $file"
    return 0
}

if [ $# -ne 3 ]; then
    echo "Error: no arguments supplied."
    echo "Usage: test.sh <cmd> <input_dir> <res_dir>"
    exit 1
fi

run_tests "$1" "$2" "$3";

if [ $ERRS -ne 0 ]; then
    echo -e "\nRan $TESTS tests, $ERRS failed! ('out/' left for investigation)\n"
    exit 1
fi

# rm -rf out
echo -e "\nRan $TESTS tests without error. Good job!\n"
