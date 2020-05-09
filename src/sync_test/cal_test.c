//
// Created by root on 11/17/19.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef struct {
    int res;
    bool is_wait;

    pthread_cond_t cond;
    pthread_mutexattr_t mutex;
} Result;

void *set_fn(void *arg) {
    int i = 1, sum = 0;
    for (; i <= 100; i++) {
        sum += i;
    }
    Result *r = (Result *) arg;
    r->res = sum;

    pthread_mutex_lock(&r->mutex);
    while (!r->is_wait) {
        pthread_mutex_unlock(&r->mutex);
        usleep(100);
        pthread_mutex_lock(&r->mutex);
    }
    pthread_mutex_unlock(&r->mutex);

    pthread_cond_broadcast(&r->cond);

    return NULL;
}

void *get_fn(void *arg) {
    Result *r = (Result *) arg;

    pthread_mutex_lock(&r->mutex);
    r->is_wait = true;
    pthread_cond_wait(&r->cond, &r->mutex);
    pthread_mutex_unlock(&r->mutex);
    int res = r->res;
    printf("res=%d", res);
    return NULL;
}

int main(void) {
    Result r;
    r.is_wait = false;
    pthread_cond_init(&r.cond, NULL);
    pthread_mutex_init(&r.mutex, NULL);

    int err;
    pthread_t cal, get;
    if ((err = pthread_create(&cal, NULL, set_fn, (void *) &r)) != 0) {
        perror("pthread create error");
    }
    if ((err = pthread_create(&get, NULL, get_fn, (void *) &r)) != 0) {
        perror("pthread create error");
    }
    pthread_join(cal, NULL);
    pthread_join(get, NULL);

    pthread_cond_destroy(&r.cond);
    pthread_cond_destroy(&r.mutex);
    return 0;
}