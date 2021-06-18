//
// Created by Admin on 2021/6/18.
//

#include <stdlib.h>

//覆写malloc

void *cover_malloc(size_t size) {
    return malloc(size);
}

void *cover_free(void *ptr) {
    free(ptr);
}