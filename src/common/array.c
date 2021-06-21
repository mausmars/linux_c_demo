#include "array.h"

Array *createArray(int cap) {
    Array *list = (Array *) cover_malloc(sizeof(Array));
    if (list == NULL) {
        fprintf(stderr, "create Array failed.\n");
        return NULL;
    }
    memset(list, 0, sizeof(list));
    list->data = (pointer *) cover_malloc(sizeof(pointer *) * cap);
    if (list->data == NULL) {
        fprintf(stderr, "malloc data space failed.\n");
        return NULL;
    }
    list->capacity = cap;
    return list;
}

void destroyArray(Array *list) {
    if (list == NULL) {
        return;
    }
    if (list->data) {
        cover_free(list->data);
    }
    cover_free(list);
}

int lengthArray(Array *list) {
    Array *array = (Array *) list;
    return array->capacity;
}

int insertArray(Array *list, any node, int index) {
    if (list == NULL) {
        return -1;
    }
    if (index < 0) {
        return -2;
    }
    if (index >= list->capacity) {
        fprintf(stdout, "Array out of bounds \n");
        return -3;
    }
    list->data[index] = (pointer) node;
    return 0;
}

any indexArray(Array *list, int index) {
    if (list == NULL || index < 0 || index >= list->capacity) {
        fprintf(stderr, "wrong arguments\n");
        return NULL;
    }
    return (any) list->data[index];
}
