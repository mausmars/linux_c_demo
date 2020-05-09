#include "account.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

Account *create_account(int code, double balance) {
    Account *a = (Account *) malloc(sizeof(Account));
    assert(a != NULL);
    a->code = code;
    a->balance = balance;

    if (a->isRWLock == true) {
        pthread_rwlockattr_init(&a->rwlockattr);
        pthread_rwlock_init(&a->rwlock, &a->rwlockattr);
    } else {
        pthread_mutexattr_init(&a->mutexattr);
//    pthread_mutexattr_settype(&a->mutexattr,PTHREAD_MUTEX_ERRORCHECK);
//    pthread_mutexattr_settype(&a->mutexattr,PTHREAD_MUTEX_NORMAL);
//    pthread_mutexattr_settype(&a->mutexattr,PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&a->mutex, &a->mutexattr);
    }
    return a;
};

void destroy_account(Account *a) {
    assert(a != NULL);

    if (a->isRWLock == true) {
        pthread_rwlockattr_destroy(&a->rwlockattr);
        pthread_rwlockattr_destroy(&a->rwlock);
    } else {
        pthread_mutexattr_destroy(&a->mutexattr);
        pthread_mutex_destroy(&a->mutex);
    }
    free(a);
};

double withdraw(Account *a, double amt) {
    assert(a != NULL);
    if (a->isRWLock == true) {
        pthread_rwlock_wrlock(&a->rwlock);
    } else {
        pthread_mutex_lock(&a->mutex);
    }
    if (amt < 0 || amt > a->balance) {
        if (a->isRWLock == true) {
            pthread_rwlock_unlock(&a->rwlock);
        } else {
            pthread_mutex_unlock(&a->mutex);
        }
        return 0.0;
    }
    double balance = a->balance;
    sleep(1);
    balance -= amt;
    a->balance = balance;

    if (a->isRWLock == true) {
        pthread_rwlock_unlock(&a->rwlock);
    } else {
        pthread_mutex_unlock(&a->mutex);
    }
    return amt;
};

double deposity(Account *a, double amt) {
    assert(a != NULL);
    if (amt < 0) {
        return 0.0;
    }
    if (a->isRWLock == true) {
        pthread_rwlock_wrlock(&a->rwlock);
    } else {
        pthread_mutex_lock(&a->mutex);
    }
    double balance = a->balance;
    sleep(1);
    balance += amt;
    a->balance = balance;

    if (a->isRWLock == true) {
        pthread_rwlock_unlock(&a->rwlock);
    } else {
        pthread_mutex_unlock(&a->mutex);
    }

    return amt;
};

double get_balance(Account *a) {
    assert(a != NULL);
    if (a->isRWLock == true) {
        pthread_rwlock_rdlock(&a->rwlock);
    } else {
        pthread_mutex_lock(&a->mutex);
    }
    double balance = a->balance;
    if (a->isRWLock == true) {
        pthread_rwlock_unlock(&a->rwlock);
    } else {
        pthread_mutex_unlock(&a->mutex);
    }
    return balance;
};

