//多线程访问数据结构的不同字段

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "padding.h"

PaddingData data;

void *thread_1(void) {
    for (int i = 0; i < 1000000000; i++) {
        data.a = 0;
    }
}

void *thread_2(void) {
    for (int i = 0; i < 1000000000; i++) {
        data.b = 0;
    }
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, (void *) thread_1, NULL);
    pthread_create(&t2, NULL, (void *) thread_2, NULL);

    printf("thread t1=%lu\n", (u_int64_t) t1);
    printf("thread t2=%lu\n", (u_int64_t) t2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
