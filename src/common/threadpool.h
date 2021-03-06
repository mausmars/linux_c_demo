//
// Created by root on 3/31/20.
//

#ifndef DEMO_LINUXC_THREADPOOL_H
#define DEMO_LINUXC_THREADPOOL_H

#include <stdio.h>
#include <pthread.h>

#include "nolock_queue.h"

//线程工作函数
void *work(void *params);

typedef struct {
    int size;
} ThreadPoolConfig;

typedef struct {

} Worker;

typedef struct {
    ThreadPoolConfig *config;
    pthread_t *pt;              //线程数组
    QueueNode **queueNode;      //队列

} ThreadPool;

extern ThreadPoolConfig *createThreadPoolConfig();

extern ThreadPool *createThreadPool(ThreadPoolConfig *config);

#endif //DEMO_LINUXC_THREADPOOL_H
