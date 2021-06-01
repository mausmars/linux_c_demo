//定时信号的使用

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void print(int n) {
    printf("%s\n", "hello,world");
}

int main(void) {
    int res = 0;
    struct itimerval tick;

    signal(SIGALRM, print);

    tick.it_value.tv_sec = 0;   //定时延时时间
    tick.it_value.tv_usec = 1;  //延时之后每多少长时间触发一次定时事件
    tick.it_interval.tv_sec = 0;
    tick.it_interval.tv_usec = 100000;

    res = setitimer(ITIMER_REAL, &tick, NULL);
    if (res) {
        printf("set timer failed!!!\n");
    }
    while (1) {
        pause();
    }
    return 0;
}