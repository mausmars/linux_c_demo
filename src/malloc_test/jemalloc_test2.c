#include <stdlib.h>
#include <jemalloc/jemalloc.h>

//cc jemalloc_test2.c -o jemalloc_test2 -I`jemalloc-config --includedir` -L`jemalloc-config --libdir` -Wl,-rpath,`jemalloc-config --libdir` -ljemalloc `jemalloc-config --libs`

void do_something(size_t i) {
    // Leak some memory.
//    malloc(i * 100);
    malloc(1024);        //100字节
}

int main(int argc, char **argv) {
    for (size_t i = 0; i < 10; i++) {
        do_something(i);
    }
    // Dump allocator statistics to stderr.
    malloc_stats_print(NULL, NULL, NULL);
    return 0;
}