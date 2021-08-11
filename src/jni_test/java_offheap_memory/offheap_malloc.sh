#!/bin/sh

$JAVA_HOME/bin/javac MallocTest.java

export LD_PRELOAD=$JEMALLOC_HOME/lib/libjemalloc.so
#export MALLOC_CONF="prof:true,lg_prof_sample:0,lg_prof_interval:30,prof_prefix:jeprof.out"
#export MALLOC_CONF="prof_leak:true,lg_prof_sample:0,prof_final:true,prof_prefix:jeprof.out"
export MALLOC_CONF="prof_leak:true,lg_prof_sample:0,prof_final:true"

$JAVA_HOME/bin/java -Djava.library.path=lib MallocTest