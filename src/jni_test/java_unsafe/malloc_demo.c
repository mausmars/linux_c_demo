#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("enter\n");

    int size = 10 * 1024 * 1024;

    void *p = malloc(1);
    free(p);
    printf("left p=%p\n", p);
    printf("enter2\n");
    void *p2 = malloc(size);
    free(p2);
    printf("left2 p=%p\n", p2);
}