#include <stdio.h>
#include <stdlib.h>
#include <jemalloc/jemalloc.h>

// 动态编译
// gcc -o mem_leak_test1 mem_leak_test1.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -ljemalloc

void do_something(size_t i) {
    // Leak some memory.
    je_malloc(i * 1024);
}

void do_something_else(size_t i) {
    // Leak some memory.
    je_malloc(i * 4096);
}

size_t *do_something_2048(size_t i) {
    // Leak some memory.
    size_t *point = je_malloc(i * 2048);
    return point;
}

int main(int argc, char **argv) {
//    setenv("MALLOC_CONF", "prof:true,prof_gdump:true", 1);
//    setenv("MALLOC_CONF", "prof:true,prof_active:false,prof_prefix:jeprof.out", 1);

//    setenv("MALLOC_CONF", "prof:true,prof_active:false,prof_prefix:test1", 1);

    size_t i, sz;
    for (i = 0; i < 80; i++) {
        do_something(i);
    }
    je_mallctl("prof.dump", NULL, NULL, NULL, 0);

    bool active = true;
    je_mallctl("prof.active", NULL, NULL, &active, sizeof(bool));

    for (i = 0; i < 40; i++) {
        do_something_else(i);
    }
    je_mallctl("prof.dump", NULL, NULL, NULL, 0);

    int count = 40;
    int *points[count];
    for (i = 0; i < count; i++) {
        size_t *point = do_something_2048(i);
        points[i] = point;
    }
    je_mallctl("prof.dump", NULL, NULL, NULL, 0);
    //free points
    for (i = 0; i < count; i++) {
        je_free(points[i]);
    }
    je_mallctl("prof.dump", NULL, NULL, NULL, 0);

    return 0;
}
