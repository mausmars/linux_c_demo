#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include "model.h"

/**
type __sync_fetch_and_add (type *ptr, type value, ...)
type __sync_fetch_and_sub (type *ptr, type value, ...)
type __sync_fetch_and_or (type *ptr, type value, ...)
type __sync_fetch_and_and (type *ptr, type value, ...)
type __sync_fetch_and_xor (type *ptr, type value, ...)
type __sync_fetch_and_nand (type *ptr, type value, ...)

type __sync_add_and_fetch (type *ptr, type value, ...)
type __sync_sub_and_fetch (type *ptr, type value, ...)
type __sync_or_and_fetch (type *ptr, type value, ...)
type __sync_and_and_fetch (type *ptr, type value, ...)
type __sync_xor_and_fetch (type *ptr, type value, ...)
type __sync_nand_and_fetch (type *ptr, type value, ...)
 */

void *cleanup(void *param) {
    AhreadParam *p = (AhreadParam *) param;
    printf("cleanup threadid=%d\n", p->threadId);
    free(param);
}

//need volatile ??
void *test_func(void *param) {
    pthread_cleanup_push(cleanup, param) ;
            AhreadParam *p = (AhreadParam *) param;
            for (int i = 0; i < 2; ++i) {
                int temp = __sync_add_and_fetch(p->count, 1);
//        int temp = *p->count + 1;
//        sleep(1);
//        *p->count = temp;

                printf("threadId=%d, v=%d\n", p->threadId, temp);
            }
    pthread_cleanup_pop(1);
    return NULL; //  pthread_exit(NULL)
}


int main(int argc, const char *argv[]) {
    int threadCount = 3;

    int count = 0;

    pthread_t id[threadCount];
    for (int i = 0; i < threadCount; ++i) {
        AhreadParam *param = (AhreadParam *) malloc(sizeof(AhreadParam));
        param->threadId = i;
        param->count = &count;

        pthread_create(&id[i], NULL, test_func, param);
    }

    printf("main thread id: %lx\n", pthread_self());
    for (int i = 0; i < threadCount; ++i) {
        pthread_join(id[i], NULL);
    }
    printf("%d\n", count);
    return 0;
}
