#!/bin/bash

heap_file_path="heap_file"

#删除之前的编译文件
rm -rf prof_test
#删除之前的 heap 文件
rm -rf $heap_file_path/*.heap
#删除之前的 pdf 文件
rm -rf $heap_file_path/*.pdf

#编译
#gcc -DJEMALLOC_NO_DEMANGLE -static -o prof_test prof_test.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -I/usr/local/libunwind/include -L/usr/local/libunwind/lib -lunwind -ljemalloc -lpthread -ldl -lm
gcc -o prof_test prof_test.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -I/usr/local/libunwind/include -L/usr/local/libunwind/lib -lunwind -ljemalloc -lpthread -ldl -lm


#设置环境变量 prof_active设置激活状态
JE_MALLOC_CONF="prof_leak:true,lg_prof_sample:0,prof_final:true,prof_prefix:$heap_file_path/test2"
LD_PRELOAD=/usr/local/jemalloc/lib/libjemalloc.so.2
echo LD_PRELOAD = $LD_PRELOAD
echo JE_MALLOC_CONF = $JE_MALLOC_CONF

#执行
./prof_test

index=0
for file in $heap_file_path/*.heap
do
  echo $file
  index=$((index+1))
  jeprof --show_bytes --pdf prof_test $file > $heap_file_path/show_test_$index.pdf
done



