//
// Created by Admin on 2021/6/18.
//

#ifndef LINUXC_DEMO_MEMORY_MGR_H
#define LINUXC_DEMO_MEMORY_MGR_H

#include <stdlib.h>

extern void *cover_malloc(size_t size);

extern void *cover_free(void *ptr);

#endif //LINUXC_DEMO_MEMORY_MGR_H
