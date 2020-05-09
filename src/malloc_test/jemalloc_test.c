//
// Created by root on 12/10/19.
//https://www.sunxidong.com/108.html
/**
 *  gcc jemalloc_test.c -o a1.out -DUSE_JEMALLOC -O2 -L/usr/local/jemalloc/lib -ljemalloc
 *  gcc jemalloc_test.c -o a2.out -O2
 *
 * 如果将程序源码中的size = rand() & 0x0000000000000fff;一行注释掉，让程序申请固定大小的内存块，得到三组数据：
 * 这种情况下使用jemalloc比普通malloc版本的性能提升将近一倍
 *
 * 同时比各自的随机大小内存块版本提升大约也有三四倍。
 */

#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <jemalloc/jemalloc.h>

#define MSECOND 1000000

int main(void) {
    int i = 0;
    char pad = 0;
    char *ptr = NULL;
    size_t size = 128;
    float timeuse = 0;
    struct timeval tpstart;
    struct timeval tpend;
    int loops = 100000000;

    srand((int) time(0));

    gettimeofday(&tpstart, NULL);
    for (i = 0; i < loops; i++) {
//        size = rand() & 0x0000000000000fff;
        ptr = malloc(size);
        pad = rand() & 0xff;
        memset(ptr, pad, size);
        free(ptr);
    }
    gettimeofday(&tpend, NULL);

    timeuse = MSECOND * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    timeuse /= MSECOND;
    printf("Used Time [%f] with [%d] loops\n", timeuse, loops);

    return 0;
}