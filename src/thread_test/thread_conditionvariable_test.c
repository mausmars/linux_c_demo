#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

/**
 * Condition Variable
 线程间的同步还有这样一种情况：线程A需要等某个条件成立才能继续往下执行，现在这个条件不成立，线程A就阻塞等待，
 而线程B在执行过程中使这个条件成立了，就唤醒线程A继续执行。在pthread库中通过条件变量（Condition Variable）
 来阻塞等待一个条件，或者唤醒等待这个条件的线程。Condition Variable用pthread_cond_t类型的变量表示，可以这样初始化和销毁：

 #include <pthread.h>

 int pthread_cond_destroy(pthread_cond_t *cond);
 int pthread_cond_init(pthread_cond_t *restrict cond,
 const pthread_condattr_t *restrict attr);
 pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
 返回值：成功返回0，失败返回错误号。

 和Mutex的初始化和销毁类似，pthread_cond_init函数初始化一个Condition Variable，attr参数为NULL则表示缺省属性，
 pthread_cond_destroy函数销毁一个Condition Variable。如果Condition Variable是静态分配的，也可以用宏定义
 PTHEAD_COND_INITIALIZER初始化，相当于用pthread_cond_init函数初始化并且attr参数为NULL。Condition Variable的
 操作可以用下列函数：

 #include <pthread.h>

 int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
 int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
 int pthread_cond_broadcast(pthread_cond_t *cond);
 int pthread_cond_signal(pthread_cond_t *cond);
 返回值：成功返回0，失败返回错误号。
 */

struct msg {
	struct msg *next;
	int num;
};

struct msg *head;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p) {
	struct msg *mp;

	for (;;) {
		pthread_mutex_lock(&lock); //加锁
		while (head == NULL) {
			pthread_cond_wait(&has_product, &lock); //如果没有消息等待条件（wait）
		}
		mp = head;
		head = mp->next;
		pthread_mutex_unlock(&lock); //解锁

		printf("Consume %d\n", mp->num);
		free(mp);
		sleep(rand() % 5);
	}
}

void *producer(void *p) {
	struct msg *mp;
	for (;;) {
		mp = malloc(sizeof(struct msg));

		pthread_mutex_lock(&lock); //加锁
		mp->next = head;
		mp->num = rand() % 1000;
		head = mp;
		printf("Produce %d\n", mp->num);
		pthread_mutex_unlock(&lock); //解锁

		pthread_cond_signal(&has_product); //通知条件（notify）

		sleep(rand() % 5);
	}
}

int main(int argc, char *argv[]) {
	pthread_t pid, cid;

	srand(time(NULL));
	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	return 0;
}
