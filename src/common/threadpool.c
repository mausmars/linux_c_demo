//
// Created by root on 3/31/20.
//

#include "threadpool.h"

void *work(void *params) {
    printf("work");
}

ThreadPoolConfig *createThreadPoolConfig() {
    ThreadPoolConfig *config = (ThreadPoolConfig *) cover_malloc(sizeof(ThreadPoolConfig));
    config->size = 5;
    return config;
}

ThreadPool *createThreadPool(ThreadPoolConfig *config) {
    for (int i = 0; i < config->size; i++) {
        pthread_create(&work, NULL, &work, NULL);
    };
}