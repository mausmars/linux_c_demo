#!/bin/sh

$JAVA_HOME/bin/javac -XDignore.symbol.file UnsafeTest.java

export LD_PRELOAD=$JEMALLOC_HOME/lib/libjemalloc.so
#export MALLOC_CONF="prof_leak:true,lg_prof_sample:0,lg_prof_interval:30,prof_final:true,prof_prefix:jeprof.out"
export MALLOC_CONF=prof_leak:true,lg_prof_sample:0,prof_final:true
#export MALLOC_CONF=prof:true,lg_prof_interval:30,lg_prof_sample:17

$JAVA_HOME/bin/java UnsafeTest