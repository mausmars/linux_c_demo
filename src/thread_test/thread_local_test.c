#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    pthread_key_t key
} ThreadParam;

void key_destrutor(void *value) {
    printf("key_destrutor \n");
    /* 这个例子中，关联key的值并没有malloc等操作，因此不用做释放动作。 */
    return (void) 0;
}

void *thread_handler1(void *args) {
    ThreadParam *tp = (ThreadParam *) args;
    int num = 100;
    pthread_setspecific(tp->key, &num);
    pthread_t tid = pthread_self();

    printf("t1 sleep \n");
    sleep(2);

    int *v = pthread_getspecific(tp->key);
    printf("t1 v=%d threadId=%lu\n", *v, (u_int64_t) tid);
}

void *thread_handler2(void *args) {
    ThreadParam *tp = (ThreadParam *) args;
    int num = 200;
    pthread_setspecific(tp->key, &num);
    pthread_t tid = pthread_self();

    printf("t2 sleep \n");
    sleep(2);

    int *v = pthread_getspecific(tp->key);
    printf("t2 v=%d threadId=%lu\n", *v, (u_int64_t) tid);
}

int main() {
    pthread_key_t key;
    pthread_t t1, t2;

    /* 创建一个key */
    pthread_key_create(&key, key_destrutor);

    ThreadParam *tp1 = (ThreadParam *) malloc(sizeof(ThreadParam));
    tp1->key = key;
    ThreadParam *tp2 = (ThreadParam *) malloc(sizeof(ThreadParam));
    tp2->key = key;

    pthread_create(&t1, NULL, thread_handler1, tp1);
    pthread_create(&t2, NULL, thread_handler2, tp2);

    printf("threadId1=%lu\n", (u_int64_t) t1);
    printf("threadId2=%lu\n", (u_int64_t) t2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    free(tp1);
    free(tp2);
    pthread_key_delete(key);

    return 0;
}
