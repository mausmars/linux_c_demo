#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("enter\n");
    void *p = malloc(1);
    free(p);
    printf("left p=%p\n", p);
    printf("enter2\n");
    void *p2 = malloc(2);
    free(p2);
    printf("left2 p=%p\n", p2);
}