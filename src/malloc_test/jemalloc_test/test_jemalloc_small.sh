#!/bin/bash

rm -rf jemalloc_small_test

ulimit -c unlimited

echo L1 cache line size
getconf LEVEL1_DCACHE_LINESIZE

gcc -g -o jemalloc_small_test jemalloc_small_test.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -ljemalloc -std=c99

echo "./jemalloc_small_test"
./jemalloc_small_test
