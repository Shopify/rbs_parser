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

    if ! ("$cmd" "$file" | sed 's/typed: true/typed: __STDLIB_INTERNAL/') > "$test_out" 2> "$test_err"; then
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(command failed see $test_err)\033[1;37m"
        ERRS=$((ERRS+1))
        return 1
    fi

    if ! (cd sorbet && bundle exec srb tc --no-config "../$test_out") >> "$test_err" 2>&1; then
        echo -e " * [\033[1;31mKO\033[0;37m] $file \033[1;90m(command failed see $test_err)\033[1;37m"
        ERRS=$((ERRS+1))
        return 1
    fi

    echo -e " * [\033[1;32mOK\033[0;37m] $file"
    return 0
}

if [ $# -ne 0 ]; then
    echo "Error: no arguments supplied."
    echo "Usage: test_with_sorbet.sh"
    exit 1
fi

# Compile RBIS

out_dir="out"
rm -rf "$out_dir"
mkdir -p "$out_dir"

echo "Test RBI files with Sorbet:"
for file in $(find rbi_generation -name "*.rbs" | sort); do
    run_test  "$file" "$out_dir"
done

if [ $ERRS -ne 0 ]; then
    echo -e "\nTried $TESTS RBI files with Sorbet, $ERRS errors! (see 'test/out/*.err' for investigation)\n"
    exit 1
fi

# rm -rf out
echo -e "\nRan $TESTS tests without error. Good job!\n"
