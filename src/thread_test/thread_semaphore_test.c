#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

/**
 *Semaphore
 Mutex变量是非0即1的，可看作一种资源的可用数量，初始化时Mutex是1，表示有一个可用资源，加锁时获得该资源，将Mutex减到0，
 表示不再有可用资源，解锁时释放该资源，将Mutex重新加到1，表示又有了一个可用资源。

 信号量（Semaphore）和Mutex类似，表示可用资源的数量，和Mutex不同的是这个数量可以大于1。

 本节介绍的是POSIX semaphore库函数，详见sem_overview(7)，这种信号量不仅可用于同一进程的线程间同步，也可用于不同进程间的同步。

 #include <semaphore.h>

 int sem_init(sem_t *sem, int pshared, unsigned int value);
 int sem_wait(sem_t *sem);
 int sem_trywait(sem_t *sem);
 int sem_post(sem_t * sem);
 int sem_destroy(sem_t * sem);

 semaphore变量的类型为sem_t，sem_init()初始化一个semaphore变量，value参数表示可用资源的数量，pshared参数为0表示信号
 量用于同一进程的线程间同步，本节只介绍这种情况。在用完semaphore变量之后应该调用sem_destroy()释放与semaphore相关的资源。

 调用sem_wait()可以获得资源，使semaphore的值减1，如果调用sem_wait()时semaphore的值已经是0，则挂起等待。如果不希望挂起等待，
 可以调用sem_trywait()。调用sem_post()可以释放资源，使semaphore的值加1，同时唤醒挂起等待的线程。
 */
#define NUM 5
int queue[NUM];
sem_t blank_number, product_number;

void *producer(void *arg) {
	static int p = 0;
	while (1) {
		sem_wait(&blank_number); //sem_wait()可以获得资源，使semaphore的值减1,semaphore的值已经是0，则挂起等待
		queue[p] = rand() % 1000;
		printf("Produce %d\n", queue[p]);
		p = (p + 1) % NUM;
		sleep(rand() % 5);
		sem_post(&product_number); //sem_post()可以释放资源，使semaphore的值加1，同时唤醒挂起等待的线程
	}
}

void *consumer(void *arg) {
	static int c = 0;
	while (1) {
		sem_wait(&product_number);
		printf("Consume %d\n", queue[c]);
		c = (c + 1) % NUM;
		sleep(rand() % 5);
		sem_post(&blank_number);
	}
}

int main(int argc, char *argv[]) {
	pthread_t pid, cid;

	sem_init(&blank_number, 0, NUM);    //初始化信号量
	sem_init(&product_number, 0, 0);

	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);

	pthread_join(pid, NULL);
	pthread_join(cid, NULL);

	sem_destroy(&blank_number);//销毁信号量
	sem_destroy(&product_number);
	return 0;
}
