//
// Created by root on 3/31/20.
//

#include "threadpool.h"

ThreadPoolConfig *createThreadPoolConfig() {
    ThreadPoolConfig *config = (ThreadPoolConfig *) malloc(sizeof(ThreadPoolConfig));
    config->size = 5;
    return config;
}

void *work(void *);

ThreadPool *createThreadPool(ThreadPoolConfig *config) {
    for (int i = 0; i < config->size; i++) {
        pthread_create(&tidA, NULL, &work, NULL);
    };
}