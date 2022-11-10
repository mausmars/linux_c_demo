#!/bin/bash

JE_MALLOC_CONF="prof:true,prof_active:false,prof_prefix:test1"
LD_PRELOAD=/usr/local/jemalloc/lib/libjemalloc.so.2

echo LD_PRELOAD = $LD_PRELOAD
echo JE_MALLOC_CONF = $JE_MALLOC_CONF

./mem_leak_test1