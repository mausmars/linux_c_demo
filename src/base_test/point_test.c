#include <stdio.h>
#include <string.h>

struct testA {
    char a;
};

struct testB {
    int a;
};

int main() {
    char dataA[20];
    memset(&dataA, 0, sizeof(dataA));
    struct testA *tA = (struct testA *) dataA;
    tA->a = 1;
    tA += 1;
    tA->a = 1;
    for (int i = 0; i < 20; i++) {
        printf("%d ", dataA[i]);
    }
    printf("\r\n------------------------------\r\n");
    char dataB[20];
    memset(&dataB, 0, sizeof(dataB));
    struct testB *tB = (struct testB *) dataB;
    tB->a = 1;
    tB += 1;
    tB->a = 1;
    for (int i = 0; i < 20; i++) {
        printf("%d ", dataB[i]);
    }
    printf("\r\n------------------------------\r\n");
    char dataC[20];
    memset(&dataC, 0, sizeof(dataC));
    char *pointC = dataC;
    *pointC = 1;
    pointC += 1;
    *pointC = 1;
    for (int i = 0; i < 20; i++) {
        printf("%d ", dataC[i]);
    }
    printf("\r\n------------------------------\r\n");

}
