#include <stdio.h>
#include <stdlib.h>
#include <jemalloc/jemalloc.h>
#include <unistd.h>

size_t *malloc_1b(size_t i) {
    size_t *point = je_malloc(i);    // 1b
    return point;
}

size_t *malloc_1k(size_t i) {
    size_t *point = je_malloc(i * 1024);    // 1k
    return point;
}

size_t *malloc_1m(size_t i) {
    size_t *point = je_malloc(i * 1024 * 1024);    // 1m
    return point;
}

// 激活 heap
int active_heap() {
    bool active = true;
    je_mallctl("prof.active", NULL, NULL, &active, sizeof(bool));
}


//创建 heap 文件
int create_heap_file(const char *fileName) {
    je_mallctl("prof.dump", NULL, NULL, &fileName, sizeof(const char *));
}


int main(int argc, char **argv) {
//    setenv("MALLOC_CONF", "prof:true,prof_gdump:true", 1);
//    setenv("MALLOC_CONF", "prof:true,prof_active:false,prof_prefix:jeprof.out", 1);
//    setenv("MALLOC_CONF", "prof:true,prof_active:false,prof_prefix:test1", 1);

    active_heap();

    size_t *point1 = malloc_1b(1);
//    create_heap_file("test_1.heap");
    printf("------------------------\r\n");
    printf("point1=%p \r\n", point1);
    printf("------------------------\r\n");
    size_t *point2 = malloc_1k(4);
//    je_free(point2);
//    create_heap_file("test_2.heap");
    printf("point2=%p \r\n", point2);
    printf("------------------------\r\n");
    size_t *point3 = malloc_1m(1);
    je_free(point3);
    printf("point3=%p \r\n", point3);
//    create_heap_file("test_3.heap");
    printf("------------------------\r\n");
//    int count = 10;
//    int *points[count];
//    for (size_t i = 0; i < count; i++) {
//        size_t *point = malloc_1m(1);
//        points[i] = point;
//    }
//    create_heap_file("test3_2.heap");
//    //free points
//    for (size_t i = 0; i < count; i++) {
//        je_free(points[i]);
//    }
//    create_heap_file("test3_3.heap");

    return 0;
}
