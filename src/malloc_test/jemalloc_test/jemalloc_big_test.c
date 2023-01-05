#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include <time.h>

// gcc -o jemalloc_big_test jemalloc_big_test.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -ljemalloc -std=c99

typedef char byte;

typedef struct {
    byte *point;
    int size;
} Data;

Data *create_data(int size) {
    Data *data = je_malloc(sizeof(Data));
    data->point = je_malloc(size);
    data->size = size;
    return data;
}

Data *malloc_b(int i) {
    return create_data(i * 1); // 1b
}

Data *malloc_k(int i) {
    return create_data(i * 1024); // 1k
}

Data *malloc_m(int i) {
    return create_data(i * 1024 * 1024); // 1m
}

Data *malloc_g(int i) {
    return create_data(i * 1024 * 1024 * 1024); // 1g
}

void set_value(Data *data) {
    //*** 设置值了才会占用内存。je_malloc只分配虚拟地址，没有分配物理内存 ***
    //如果free内存不够，这里执行的非常慢？？？ 为啥呢？
    clock_t start = clock();
    for (int i = 0; i < data->size; i++) {
        *(data->point + i) = 1;
    }
    clock_t finish = clock();
    double duration = (double) (finish - start) / CLOCKS_PER_SEC;
    printf("set_value %fs\n", duration);
}

int main() {
    int count = 100;
    Data *datas[count];
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
                Data *data = malloc_m(512);
                printf("分配虚拟地址 over \n");
                set_value(data);
                printf("设置内存 over \n");
                datas[index] = data;
                printf("总个数 %d \n", index + 1);
            }
        } else if (num == 2) {
            if (index >= 0) {
                printf("释放内存 \n");
                Data *data = datas[index];
                je_free(data->point);
                je_free(data);
                //free掉的内存回收到系统的free内存上了
                index--;
                printf("总个数 %d \n", index + 1);
            }
        } else if (num == 3) {
            printf("exit... *_* \n");
            break;
        }
    }
}
