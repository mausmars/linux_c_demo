#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>

#define gettid() syscall(SYS_gettid)

void *threadFunc(void *p) {
    printf("threadFunc is %d\n", gettid());

    int i = 0;
    while (1) {
        sleep(1);
    }

    return NULL;
}

int main() {
    printf("main thread id is %d\n", gettid());

    pthread_t id;
    pthread_create(&id, NULL, threadFunc, NULL);
    pthread_create(&id, NULL, threadFunc, NULL);
    pthread_create(&id, NULL, threadFunc, NULL);
    pthread_create(&id, NULL, threadFunc, NULL);
    pthread_create(&id, NULL, threadFunc, NULL);
    pthread_create(&id, NULL, threadFunc, NULL);

    int i = 0;
    while (1) {
        sleep(1);
    }
    return 0;
}