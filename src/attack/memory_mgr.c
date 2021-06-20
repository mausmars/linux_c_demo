//覆写malloc

#include "memory_mgr.h"

extern void *cover_malloc(size_t size) {
    return malloc(size);
}

extern void *cover_free(void *ptr) {
    free(ptr);
}