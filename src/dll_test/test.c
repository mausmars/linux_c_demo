#include <stdio.h>
#include "math/math_test.h"

int main(int argc, char *argv[]) {
    int a = 10, b = -2, c = 100;
    printf(">>> max among (10, -2, 100) is %d \n", math_max(a, b, c));
    return 0;
}