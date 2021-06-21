//
// Created by Admin on 2021/6/18.
//

#ifndef LINUXC_DEMO_MEMORY_H
#define LINUXC_DEMO_MEMORY_H

#include <stdlib.h>

void *cover_malloc(size_t size);

void *cover_free(void *ptr);

#endif //LINUXC_DEMO_MEMORY_H
