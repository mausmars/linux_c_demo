//gettid () 返回调用者的线程 ID (TID)。在单线程进程，线程ID等于进程ID（PID，由getpid(2)返回）。
//在多线程进程中，所有线程具有相同的 PID，但每个线程都有唯一的 TID

#include "coroutine.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>

#include <ucontext.h>

#define gettid() syscall(SYS_gettid)

struct args {
    int n;
};

static void foo(struct schedule *S, void *ud) {
    struct args *arg = ud;
    int start = arg->n;
    int i;
    for (i = 0; i < 2; i++) {
        pthread_t thread = pthread_self();
        printf("threadId=%d, %lu, coroutine %d : %d \n", gettid(), thread, coroutine_running(S), start + i);
        //释放
        coroutine_yield(S);
    }
}

static void test1() {
    pthread_t thread = pthread_self();
    printf("main thread id is %d, %lu\n", gettid(), thread);
    struct schedule *S = coroutine_open();

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

    coroutine_close(S);
}

static void test5() {
    pthread_t thread = pthread_self();
    printf("main thread id is %d, %lu\n", gettid(), thread);
    struct schedule *S = coroutine_open();

    int coroutineCount = 5, i, isContinue;
    int coroutines[coroutineCount];
    for (i = 0; i < coroutineCount; i++) {
        struct args parsms = {i};
        int coroutine = coroutine_new(S, foo, &parsms);
        coroutines[i] = coroutine;
    }
    printf("main start\n");
    while (1) {
        isContinue = 1;
        for (i = 0; i < coroutineCount; i++) {
            int c = coroutine_status(S, coroutines[i]);
            if (c <= 0) {
                isContinue = 0;
            }
        }
        if (isContinue <= 0) {
            break;
        }
        for (i = 0; i < coroutineCount; i++) {
            coroutine_resume(S, coroutines[i]);
        }
    }
    printf("main end\n");
}


static void test2() {
    ucontext_t context;
    getcontext(&context); //先保存了一个上下文
    puts("Hello world");
    sleep(1);
    setcontext(&context); //重新执行代
}

static void func1(void *arg) {
    puts("func1 1");
    puts("func1 2");
}

static void func2(void *arg) {
    puts("func2 1");
    puts("func2 2");
}

static void test3() {
    char stack[1024 * 128];
    ucontext_t child1, child2, main;

    puts("getcontext");
    getcontext(&child1); //获取当前上下文
    child1.uc_stack.ss_sp = stack;//指定栈空间
    child1.uc_stack.ss_size = sizeof(stack);//指定栈空间大小
    child1.uc_stack.ss_flags = 0;
    child1.uc_link = &main;//设置后继上下文
    puts("makecontext func1");
    makecontext(&child1, (void (*)(void)) func1, 0);//修改上下文指向func1函数
    puts("swapcontext");
    swapcontext(&main, &child1);//切换到child上下文，保存当前上下文到main

    puts("main");//如果设置了后继上下文，func1函数指向完后会返回此处
}

int main() {
    // test1();
    // test2();
//    test3();
    test5();
    return 0;
}

