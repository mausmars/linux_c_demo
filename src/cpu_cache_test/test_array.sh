#!/bin/bash

echo L1 cache line size
getconf LEVEL1_DCACHE_LINESIZE


gcc -o array_test1 array_test1.c
gcc -o array_test2 array_test2.c
gcc -o array_test3 array_test3.c
gcc -o array_test4 array_test4.c

echo "./array_test1"
time ./array_test1

echo "./array_test2"
time ./array_test2

echo "./array_test3"
time ./array_test3

echo "./array_test4"
time ./array_test4

rm -rf array_test1
rm -rf array_test2
rm -rf array_test3
rm -rf array_test4