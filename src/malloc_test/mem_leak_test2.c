#include <stdio.h>
#include <stdlib.h>
#include <jemalloc/jemalloc.h>

// gcc -o mem_leak_test2 mem_leak_test2.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -ljemalloc
// jeprof mem_leak_test2 jeprof.15894.0.m0.heap
// (jeprof) top


//jeprof a.out --base=prof.1 prof.2
//jeprof --show_bytes --pdf  a.out jeprof.out.28954.1.m1.heap > je.pdf

void do_something(size_t i) {
    // Leak some memory.
    malloc(i * 1024);
}

void do_something_else(size_t i) {
    // Leak some memory.
    malloc(i * 4096);
}

int main(int argc, char **argv) {
    setenv("MALLOC_CONF", "prof:true,prof_active:false,prof_prefix:jeprof.out", 1);

    size_t i, sz;

    //initialization ...
    for (i = 0; i < 80; i++) {
        do_something(i);
    }
    //enter into steady-state...
    bool active = true;
    mallctl("prof.active", NULL, NULL, &active, sizeof(bool));

    for (i = 0; i < 40; i++) {
        do_something_else(i);
    }
    mallctl("prof.dump", NULL, NULL, NULL, 0);

    return (0);
}