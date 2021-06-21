//覆写malloc

#include "memory.h"

void *cover_malloc(size_t size) {
    return malloc(size);
}

void *cover_free(void *ptr) {
    free(ptr);
}