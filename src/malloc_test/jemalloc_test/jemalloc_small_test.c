#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include <time.h>

// gcc -o jemalloc_small_test jemalloc_small_test.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib -ljemalloc -std=c99

typedef char byte;
typedef char *pointer; //指针类型（32位系统 4字节，64位系统 8字节）

typedef struct {
    pointer point;
    int size;
} Data;

pointer create_data(int size) {
    Data *data = je_malloc(sizeof(Data));
    data->point = je_malloc(size);
    data->size = size;

    printf("data point %p\n", data);
    return (pointer) data;
}

pointer malloc_b(int i) {
    return create_data(i * 1); // 1b
}

pointer malloc_k(int i) {
    return create_data(i * 1024); // 1k
}

pointer malloc_m(int i) {
    return create_data(i * 1024 * 1024); // 1m
}

pointer malloc_g(int i) {
    return create_data(i * 1024 * 1024 * 1024); // 1g
}

void set_value(Data *data) {
    // *** 设置值了才会占用内存。je_malloc只分配虚拟地址，没有分配物理内存 ***
    // 如果free内存不够，这里执行的非常慢？？？ 为啥呢？
    for (int i = 0; i < data->size; i++) {
        *(data->point + i) = 1;
    }
}

//int d_cout = 1024 * 100;
int d_cout = 1;

pointer malloc_small() {
    clock_t start = clock();
    pointer ds = je_malloc(sizeof(pointer) * d_cout);

    for (int i = 0; i < d_cout; i++) {
        pointer data = malloc_k(5);
        printf("data point %p \n", data);
        set_value((Data *) data);
        ds[i] = data;
    }
    clock_t finish = clock();
    double duration = (double) (finish - start) / CLOCKS_PER_SEC;
    printf("set_value %fs \n", duration);
    printf("ds point %p \n", ds);
    printf("data point %p \n", ds[0]);
    return ds;
}

int main() {
    int count = 100;
    pointer datas = je_malloc(sizeof(pointer) * count);
    int index = -1;

    printf("sizeof(pointer) %d \n", sizeof(pointer));
    while (true) {
        printf("command: 1增加内存 2释放内存 3退出 \n");
        int num;
        // %f 匹配浮点型数据

        scanf("%d", &num);
        if (num == 1) {
            if (index < count - 1) {
                index++;
                printf("增加内存 index=%d \n", index);
                pointer ds = malloc_small();
                *(datas + index) = ds;

                printf("datas point %p \n", datas);
                printf("总个数 %d \n", index + 1);
            }
        } else if (num == 2) {
            if (index >= 0) {
                printf("释放内存 index=%d \n", index);
                pointer ds = *(datas + index);
                printf("ds point %p \n", ds);
                for (int i = 0; i < d_cout; i++) {
                    Data *data = *(ds + i);
                    je_free(data->point);
                    je_free(data);
                    printf("data point %p \n", data);
                }
                je_free(ds);

                //free掉的内存回收到系统的free内存上了
                index--;
                printf("总个数 %d \n", index + 1);
            }
        } else if (num == 3) {
            printf("exit... \n");
            break;
        }
    }
}
