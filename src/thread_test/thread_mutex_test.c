#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * Mutex用pthread_mutex_t类型的变量表示，可以这样初始化和销毁：

 #include <pthread.h>

 int pthread_mutex_destroy(pthread_mutex_t *mutex);
 int pthread_mutex_init(pthread_mutex_t *restrict mutex,
 const pthread_mutexattr_t *restrict attr);

 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 返回值：成功返回0，失败返回错误号。

 int pthread_mutex_lock(pthread_mutex_t *mutex);
 int pthread_mutex_trylock(pthread_mutex_t *mutex);
 int pthread_mutex_unlock(pthread_mutex_t *mutex);
 */

#define NLOOP 5000

int counter; /* incremented by threads */

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *);

int main(int argc, char **argv) {
	pthread_t tidA, tidB;

	pthread_create(&tidA, NULL, &doit, NULL);
	pthread_create(&tidB, NULL, &doit, NULL);

	/* wait for both threads to terminate */
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);

	return 0;
}

void *doit(void *vptr) {
	int i, val;
	/*
	 * Each thread fetches, prints, and increments the counter NLOOP times.
	 * The value of the counter should increase monotonically.
	 */
	for (i = 0; i < NLOOP; i++) {
		pthread_mutex_lock(&counter_mutex); //加锁

		val = counter;
		printf("%x: %d\n", (unsigned int) pthread_self(), val + 1);
		counter = val + 1;

		pthread_mutex_unlock(&counter_mutex); //解锁
	}
	return NULL;
}
