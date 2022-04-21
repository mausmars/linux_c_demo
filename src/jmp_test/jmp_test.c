#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf env;

void fun() {
    printf("fun() enter \n");

    //longjmp()可以在其它函数中随时返回之前的现场
    longjmp(env, 1);
    printf("fun() exit \n");
}

int main() {
    //保存当前函数的执行状态
    int ret = setjmp(env);
    if (ret == 0) {
        printf("from setjmp \n");
        fun();
    } else {
        printf("from longjmp \n");
    }
    return 0;
}