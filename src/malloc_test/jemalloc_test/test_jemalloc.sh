#!/bin/bash

echo L1 cache line size
getconf LEVEL1_DCACHE_LINESIZE

gcc -o jemalloc_test jemalloc_test.c

echo "./jemalloc_test"
./jemalloc_test

rm -rf jemalloc_test