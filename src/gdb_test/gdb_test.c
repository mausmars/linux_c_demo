/**
 * gcc -g gdb_test.c -o gdb_test
 *
 * gdb gdb_test
 * gdb ./gdb_test gdb_test.core
 */

//输入34 导致出错生成 .core文件

#include <stdio.h>

int main(int argc, char const *argv[]) {
    int i = 0;

    scanf("%d", i);
    printf("hello,程序猿编码 %d\n", i);
    return 0;
}