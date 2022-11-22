#!/bin/bash

echo L1 cache line size
getconf LEVEL1_DCACHE_LINESIZE

gcc -o padding_test1 padding_test1.c -lpthread
gcc -o padding_test2 padding_test2.c -lpthread

echo "./padding_test2"
time ./padding_test2

echo "./padding_test1"
time ./padding_test1

rm -rf padding_test1
rm -rf padding_test2
