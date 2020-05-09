#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "model.h"

/**
bool __sync_bool_compare_and_swap (type *ptr, type oldval type newval, ...)
type __sync_val_compare_and_swap (type *ptr, type oldval type newval, ...)
 */
void *cleanup(void *param) {
    AhreadParam *p = (AhreadParam *) param;
    printf("cleanup threadid=%d\n", p->threadId);
    free(param);
}

void *test_func(void *param) {
    pthread_cleanup_push(cleanup, param) ;
            AhreadParam *p = (AhreadParam *) param;
            int temp = __sync_bool_compare_and_swap(p->count, 99, 100);
            printf("threadId=%d, isSuccess=%d\n", p->threadId, temp);
    pthread_cleanup_pop(1);
    return NULL;
}

int main(int argc, const char *argv[]) {
    int threadCount = 3;
    pthread_t id[threadCount];

    int count = 99;
    for (int i = 0; i < threadCount; ++i) {
        AhreadParam *param = (AhreadParam *) malloc(sizeof(AhreadParam));
        param->threadId = i;
        param->count = &count;
        pthread_create(&id[i], NULL, test_func, param);
    }
    for (int i = 0; i < threadCount; ++i) {
        pthread_join(id[i], NULL);
    }
    printf("%d\n", count);
    return 0;
}
