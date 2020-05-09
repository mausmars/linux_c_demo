#include <sys/epoll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdarg.h>
#include <sys/eventfd.h>

typedef struct {
    int fd;
} ThreadParam;

void *doit(ThreadParam *param);


void print_sigset(sigset_t *set) {
    int i;
    for (i = 1; i < NSIG; ++i) {
        if (sigismember(set, i))
            printf("1");
        else
            printf("0");
    }
    putchar('\n');
}

void printf_and_flush(const char *__restrict format, ...) {
    printf("%s %s ", __DATE__, __TIME__);
    va_list args;       //定义一个va_list类型的变量，用来储存单个参数
    va_start(args, format); //使args指向可变参数的第一个参数
    vprintf(format, args);  //必须用vprintf等带V的
    va_end(args);       //结束可变参数的获取
}

int main(int argc, char *argv[]) {
    int fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (fd < 0) {
        perror("eventfd failed.");
        abort();
    }

    ThreadParam *threadParam = (ThreadParam *) malloc(sizeof(ThreadParam));
    threadParam->fd = fd;

    pthread_t thread;
    pthread_create(&thread, NULL, &doit, threadParam);

    puts("sleep 1s");
    sleep(1);
    puts("eventfd write");
    int ret;
    for (int i = 0; i < 5; i++) {
        eventfd_t count = 4;
        ret = eventfd_write(fd, &count);
        if (ret < 0) {
            perror("write event fd fail:");
        }
    }
    sleep(1);
//    pthread_join(thread, NULL);
    puts("end!");
    sleep(10);
}

void *doit(ThreadParam *param) {
    int epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create error");
        abort();
    }
    int fd = param->fd;

    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);

    struct epoll_event *events;
    events = calloc(2, sizeof event);
    int isRun = 1;

    while (isRun) {
        int n, i;
        n = epoll_wait(epfd, events, 2, -1);
        for (i = 0; i < n; i++) {
            if (events[i].data.fd == param->fd) {
                puts("eventfd notify");
                isRun = 0;
            } else {
                puts("error");
            }
        }
    }
}
