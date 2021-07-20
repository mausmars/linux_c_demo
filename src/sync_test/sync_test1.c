#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include "model.h"
/**
type __sync_fetch_and_add (type *ptr, type value, ...)
type __sync_fetch_and_sub (type *ptr, type value, ...)
type __sync_fetch_and_or (type *ptr, type value, ...)
type __sync_fetch_and_and (type *ptr, type value, ...)
type __sync_fetch_and_xor (type *ptr, type value, ...)
type __sync_fetch_and_nand (type *ptr, type value, ...)

type __sync_add_and_fetch (type *ptr, type value, ...)
type __sync_sub_and_fetch (type *ptr, type value, ...)
type __sync_or_and_fetch (type *ptr, type value, ...)
type __sync_and_and_fetch (type *ptr, type value, ...)
type __sync_xor_and_fetch (type *ptr, type value, ...)
type __sync_nand_and_fetch (type *ptr, type value, ...)
 */

void *cleanup(void *param) {
    AhreadParam *p = (AhreadParam *) param;
    printf("cleanup threadid=%d\n", p->threadId);
    free(param);
}

//need volatile ??
void *test_func(void *param) {
    AhreadParam *p = (AhreadParam *) param;
    for (int i = 0; i < 1000; ++i) {
//        __sync_fetch_and_add(p->count, 1);
        *p->count = *p->count + 1;
//        printf("threadId = %d , v = %d\n", p->threadId, *p->count);
    }

    pthread_cleanup_push(cleanup, param) ;
//            pthread_cleanup_push(cleanup, "test2") ;

//            pthread_cleanup_pop(0);
    pthread_cleanup_pop(1);

    int result = p->threadId;
    return result; //  pthread_exit(NULL)
}

void out_state(pthread_attr_t *attr) {
    int state;
    if (pthread_attr_getdetachstate(attr, &state) != 0) {
        perror("getdetachstate error!");
    } else {
        if (state == PTHREAD_CREATE_JOINABLE) {
            printf("joinable state\n");
        } else if (state == PTHREAD_CREATE_DETACHED) {
            printf("detached state\n");
        } else {
            printf("error state\n");
        }
    }
}

int main(int argc, const char *argv[]) {
    int threadCount = 3;

    int count = 0;

    int i = 0;
    pthread_t id[threadCount];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    out_state(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    out_state(&attr);
    pthread_attr_destroy(&attr);
    //PTHREAD_SCOPE_SYSTEM（绑定的）和PTHREAD_SCOPE_PROCESS（非绑定的）
//    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

//    sched_param param;
//    param.sched_priority=20;
//    pthread_attr_setschedparam(&attr, &param);
    int err;
    for (i = 0; i < threadCount; ++i) {
        AhreadParam *param = (AhreadParam *) malloc(sizeof(AhreadParam));
        param->threadId = i;
        param->count = &count;

        pthread_create(&id[i], &attr, test_func, param);
    }

    printf("main thread id: %lx\n", pthread_self());
    for (i = 0; i < threadCount; ++i) {
        int *result;

        if ((err = pthread_join(id[i], (void **) &result)) != 0) {
            perror("pthread join error!");
            fprintf(stderr, "%s\n", strerror(err));
        } else {
            printf("result = %d\n", (int) result);
        }
//
//        printf("result = %d\n", (XXX*) result);
//        pthread_cancel(id[i]);

    }
    printf("%d\n", count);
    return 0;
}
