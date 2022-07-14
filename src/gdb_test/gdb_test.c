/**
 * gcc -g gdb_test.c -o gdb_test
 *
 * gdb gdb_test
 * gdb ./gdb_test gdb_test.core
 */

#include <stdio.h>

void Print(int i) {
    printf("hello,程序猿编码 %d\n", i);
}

int main(int argc, char const *argv[]) {
    int i = 0;
    for (i = 1; i < 3; i++) {
        Print(i);
    }
    return 0;
}