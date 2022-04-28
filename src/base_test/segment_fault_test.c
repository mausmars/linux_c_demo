#include <stdio.h>

int main() {
    char *str = (char *) 0XFFF00000;  //使用数值表示一个明确的地址
    printf("####  %s \n", str);
    return 0;
}