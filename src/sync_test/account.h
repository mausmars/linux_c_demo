//
// Created by root on 11/17/19.
//

#ifndef DEMO_LINUXC_ACCOUNT_H
#define DEMO_LINUXC_ACCOUNT_H

#include <zconf.h>
#include <pthread.h>
#include "common.h"

typedef struct {
    int code;
    double balance;

    bool isRWLock;
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;

    pthread_rwlock_t rwlock;
    pthread_rwlockattr_t rwlockattr;
} Account;

extern Account *create_account(int code, double balance);

extern void destroy_account(Account *a);

extern double withdraw(Account *a, double amt);

extern double deposity(Account *a, double amt);

extern double get_balance(Account *a);

#endif //DEMO_LINUXC_ACCOUNT_H
