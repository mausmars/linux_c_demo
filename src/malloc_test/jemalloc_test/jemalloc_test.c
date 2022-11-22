#include <stdio.h>
#include <stdlib.h>
#include <jemalloc/jemalloc.h>
#include <unistd.h>

size_t *malloc_1b(size_t i) {
    size_t *point = je_malloc(i);    // 1b
    return point;
}

size_t *malloc_1k(size_t i) {
    size_t *point = je_malloc(i * 1024);    // 1k
    return point;
}

size_t *malloc_1m(size_t i) {
    size_t *point = je_malloc(i * 1024 * 1024);    // 1m
    return point;
}

size_t *malloc_1g(size_t i) {
    size_t *point = je_malloc(i * 1024 * 1024 * 1024);    // 1g
    return point;
}

int main(int argc, char **argv) {
    int count = 100;
    int *points[count];
    int index = -1;

    while (true) {
        printf("command: 1增加内存 2释放内存 3退出 \n");
        int num;
        // %f 匹配浮点型数据
        scanf("%d", &num);
        if (num == 1) {
            if (index < count - 1) {
                index++;
                printf("增加内存 \n");
                points[index] = malloc_1m(1);
                printf("总个数 %d \n", index + 1);
            }
        } else if (num == 2) {
            if (index >= 0) {
                printf("释放内存 \n");
                je_free(points[index]);
                index--;
                printf("总个数 %d \n", index + 1);
            }
        } else if (num == 3) {
            printf("exit... *_* \n");
            break;
        }
    }
}
