#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>

int cnt;
atomic_int acnt;

void* test(void* param) {
	int n = 0;
	for (; n < 1000; ++n) {
		++cnt;
		atomic_fetch_add(&acnt, 1);
	}
	return NULL;
}

int main(void) {
	pthread_t t[10];
	int i = 0;
	for (; i < 10; i++) {
		pthread_create(&t[i], NULL, test, NULL);
	}
	i = 0;
	for (; i < 10; i++) {
		pthread_join(t[i], NULL);
	}
	printf("acnt = %u; cnt = %u;\n", acnt, cnt);
}
//gcc -lpthread -o stdatomic_test stdatomic_test.c
