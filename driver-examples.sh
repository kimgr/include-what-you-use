#!/bin/bash

function test-invocation() {
    expected="${2:-0}"
    echo ">> Testing: $1"
    $1
    if [ "$?" != "$expected" ]; then
        echo ">>> FAIL"
    else
        echo ">>> PASS"        
    fi 
    echo ""
}

test-invocation "include-what-you-use -E tests/test.c"
test-invocation "include-what-you-use tests/test.c"
test-invocation "include-what-you-use -save-temps tests/test.c"
test-invocation "include-what-you-use -save-temps -E tests/test.c"
test-invocation "include-what-you-use -fno-integrated-as -c tests/test.c"
test-invocation "include-what-you-use -c -fembed-bitcode tests/test.c"
test-invocation "include-what-you-use -fstack-usage -c tests/test.c"
test-invocation "include-what-you-use -fdump-rtl-expand -c tests/test.c"

# Full compile and link sequence
test-invocation "include-what-you-use -c tests/test.c -o blah -lm"

# Generate PCH job
test-invocation "include-what-you-use -c tests/test.c -emit-pch -o test.c.pch"

# MacOS offloading
test-invocation "include-what-you-use -target arm64-apple-macosx11.0.0 -c -x hip tests/test.c -nogpulib -nogpuinc"

# OpenMP offloading
test-invocation "include-what-you-use -fopenmp -fopenmp-targets=nvptx64 -nogpulib -nogpuinc -O3 tests/test.c -c"

# more than one input
test-invocation "include-what-you-use tests/test.c tests/empty.cc"

# Link-only job
test-invocation "include-what-you-use file2.o lab.o -lm -o my_executable" 1

# precompiler
test-invocation "include-what-you-use -target aarch64-unknown-gnu-linux --print-supported-extensions -c tests/test.c" 1
