#include <stdio.h>

#include "max_test.h"

int max(int n1, int n2, int n3) {
    printf(">>> max \n");
    int max_num = n1;
    max_num = max_num < n2 ? n2 : max_num;
    max_num = max_num < n3 ? n3 : max_num;
    return max_num;
}