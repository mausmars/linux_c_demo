#include"arraylist.h"

//扩容list
static int expand(ArrayList *list, int size) {
    if (list == NULL || size < list->capacity) {
        fprintf(stderr, "wrong argument.\n");
        return -1;
    }
    int newSize = size;
    if (size > 2 * list->capacity) {
        newSize = 2 * list->capacity;
    }
    pointer *oldData = list->data;
    pointer *newData = cover_malloc(newSize * sizeof(pointer *));
    if (newData == NULL) {
        fprintf(stderr, "grow capacity failed.\n");
        return -1;
    }
    list->data = newData;
    memset(list->data, 0, sizeof(list->data));
    memcpy(list->data, oldData, sizeof(oldData) * list->length);
    list->capacity = newSize;
    cover_free(oldData);
    return newSize;
}

ArrayList *createArrayList(int cap) {
    ArrayList *list = (ArrayList *) cover_malloc(sizeof(ArrayList));
    if (list == NULL) {
        fprintf(stderr, "create ArrayList failed.\n");
        return NULL;
    }
    memset(list, 0, sizeof(list));
    list->data = (pointer *) cover_malloc(sizeof(pointer *) * cap);
    if (list->data == NULL) {
        fprintf(stderr, "malloc data space failed.\n");
        return NULL;
    }
    list->capacity = cap;
    list->length = 0;
    return list;
}

void destroyArrayList(ArrayList *list) {
    if (list == NULL) {
        return;
    }
    if (list->data) {
        cover_free(list->data);
    }
    cover_free(list);
}

void clearArrayList(ArrayList *list) {
    if (list == NULL) {
        return;
    }
    list->length = 0;
}

int lengthArrayList(ArrayList *list) {
    ArrayList *arrayList = (ArrayList *) list;
    return arrayList->length;
}

//插入到结尾
int insertArrayListToLast(ArrayList *list, any node) {
    if (list == NULL) {
        return -1;
    }
    if (list->length == list->capacity) {
        //扩容
        int ret = expand(list, list->capacity * 2);
        if (ret == -1) {
            return -3;
        }
    }
    list->data[list->length] = (pointer) node;
    list->length += 1;
    return 0;
}

//插入到中间
int insertArrayList(ArrayList *list, any node, int index) {
    if (list == NULL) {
        return -1;
    }
    if (index < 0) {
        return -2;
    }
    if (list->length == list->capacity) {
        //扩容
        int ret = expand(list, list->capacity * 2);
        if (ret == -1) {
            return -3;
        }
    }
    if (index > list->length) {
        return -4;
    }
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = (pointer) node;
    list->length += 1;
    return 0;
}

any indexArrayList(ArrayList *list, int index) {
    if (list == NULL || index < 0 || index > list->length) {
        fprintf(stderr, "wrong arguments\n");
        return NULL;
    }
    return (any) list->data[index];
}

any removeArrayList(ArrayList *list, int index) {
    if (list == NULL || index < 0 || index > list->length) {
        fprintf(stderr, "wrong arguments\n");
        return NULL;
    }
    any node = (any) list->data[index];
    for (int i = index + 1; i < list->length; i++) {
        list->data[i - 1] = list->data[i];
    }
    list->length--;
    return node;
}
