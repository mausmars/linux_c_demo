//
// Created by Admin on 2021/6/21.
//

#ifndef LINUXC_DEMO_ARRAY_H
#define LINUXC_DEMO_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "type.h"
#include "memory.h"

typedef struct {
    int capacity;           //容量
    pointer *data;          //数组指针
} Array;

//创建并且返回一个空的Array
Array *createArray(int cap);

//销毁一个线性表Array
void destroyArray(Array *array);

//返回一个线性表Array中的所有元素个数
int lengthArray(Array *array);

//向一个线性表Array的pos位置处插入新元素node
int insertArray(Array *array, any node, int index);

//获取一个线性表Array的pos位置处的元素
any indexArray(Array *array, int index);

#endif //LINUXC_DEMO_ARRAY_H
