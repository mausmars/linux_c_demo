#!/bin/bash

#删除之前的编译文件
rm -rf prof_test
#删除之前的 heap 文件
rm -rf *.heap
#删除之前的 pdf 文件
rm -rf *.pdf

#编译
#gcc -DJEMALLOC_NO_DEMANGLE -static -o prof_test prof_test.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -I/usr/local/libunwind/include -L/usr/local/libunwind/lib -lunwind -ljemalloc -lpthread -ldl -lm

gcc -o prof_test prof_test.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -I/usr/local/libunwind/include -L/usr/local/libunwind/lib -lunwind -ljemalloc -lpthread -ldl -lm


#设置环境变量 prof_active设置激活状态
JE_MALLOC_CONF="prof:true,prof_active:true,prof_prefix:test3"
LD_PRELOAD=/usr/local/jemalloc/lib/libjemalloc.so.2
echo LD_PRELOAD = $LD_PRELOAD
echo JE_MALLOC_CONF = $JE_MALLOC_CONF

#执行
./prof_test

jeprof --show_bytes --pdf prof_test test_1.heap > show_test_1.pdf
jeprof --show_bytes --pdf prof_test test_2.heap > show_test_2.pdf
jeprof --show_bytes --pdf prof_test test_3.heap > show_test_3.pdf

