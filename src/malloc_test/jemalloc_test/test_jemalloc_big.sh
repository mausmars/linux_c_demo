#!/bin/bash

echo L1 cache line size
getconf LEVEL1_DCACHE_LINESIZE

gcc -o jemalloc_big_test jemalloc_big_test.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -ljemalloc -std=c99

echo "./jemalloc_big_test"
./jemalloc_big_test

rm -rf jemalloc_big_test