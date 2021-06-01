//gettid () 返回调用者的线程 ID (TID)。在单线程进程，线程ID等于进程ID（PID，由getpid(2)返回）。
// 在多线程进程中，所有线程具有相同的 PID，但每个线程都有唯一的 TID

#include "coroutine.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>

#define gettid() syscall(SYS_gettid)

struct args {
    int n;
};

static void foo(struct schedule *S, void *ud) {
    struct args *arg = ud;
    int start = arg->n;
    int i;
    for (i = 0; i < 5; i++) {
        pthread_t thread = pthread_self();
        printf("threadId=%d, %lu, coroutine %d : %d \n", gettid(), thread, coroutine_running(S), start + i);
        coroutine_yield(S);
    }
}

static void test(struct schedule *S) {
    struct args arg1 = {0};
    struct args arg2 = {100};

    int co1 = coroutine_new(S, foo, &arg1);
    int co2 = coroutine_new(S, foo, &arg2);
    printf("main start\n");
    while (coroutine_status(S, co1) && coroutine_status(S, co2)) {
        coroutine_resume(S, co1);
        coroutine_resume(S, co2);
    }
    printf("main end\n");
}

int main() {
    pthread_t thread = pthread_self();
    printf("main thread id is %d, %lu\n", gettid(), thread);

    struct schedule *S = coroutine_open();
    test(S);
    coroutine_close(S);

    return 0;
}

