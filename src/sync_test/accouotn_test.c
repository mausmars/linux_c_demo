//
// Created by root on 11/17/19.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "account.h"

typedef struct {
    char name[20];
    Account *account;
    double amt;
} OperArg;

void *withdraw_fn(void *arg) {
    OperArg *oa = (OperArg *) arg;
    double amt = withdraw(oa->account, oa->amt);

    printf("%8s(0x%lx) withdraw %f from account %d\n", oa->name, pthread_self(), amt, oa->account->code);

    return NULL;
}

void *deposit_fn(void *arg) {
    OperArg *oa = (OperArg *) arg;
    double amt = deposity(oa->account, oa->amt);

    printf("%8s(0x%lx) deposity %f from account %d\n", oa->name, pthread_self(), amt, oa->account->code);

    return NULL;
}

void *check_fn(void *arg) {
    return NULL;
}

int main(int argc, const char *argv[]) {
    Account *a = create_account(100001, 10000);
    OperArg o1, o2;
    strcpy(o1.name, "boy");
    o1.account = a;
    o1.amt = 10000;

    strcpy(o2.name, "gril");
    o2.account = a;
    o2.amt = 10000;

    int err;
    pthread_t boy, girl;
    if ((err = pthread_create(&boy, NULL, withdraw_fn, (void *) &o1)) != 0) {
        perror("pthread create error");
    }
    if ((err = pthread_create(&girl, NULL, withdraw_fn, (void *) &o2)) != 0) {
        perror("pthread create error");
    }

    pthread_join(boy, NULL);
    pthread_join(girl, NULL);

    printf("account balance: %f\n", get_balance(a));
    destroy_account(a);
    return 0;
}