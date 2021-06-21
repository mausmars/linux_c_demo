//
// Created by Admin on 2021/6/20.
//

#ifndef LINUXC_DEMO_ARRAYLIST_H
#define LINUXC_DEMO_ARRAYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "type.h"
#include "memory.h"

typedef struct {
    int length;             //当前长度
    int capacity;           //容量
    pointer *data;          //数组指针
} ArrayList;

//创建并且返回一个空的ArrayList
ArrayList *createArrayList(int cap);

//销毁一个线性表ArrayList
void destroyArrayList(ArrayList *list);

//将一个线性表ArrayList中的所有元素清空
void clearArrayList(ArrayList *list);

//返回一个线性表ArrayList中的所有元素个数
int lengthArrayList(ArrayList *list);

//插入到最后一个位置
int insertArrayListToLast(ArrayList *list, any node);

//插入到length范围内的index位置
int insertArrayList(ArrayList *list, any node, int index);

//删除一个线性表ArrayList的index位置处的元素  返回值为被删除的元素，NULL表示删除失败
any removeArrayList(ArrayList *list, int index);

//获取一个线性表ArrayList的index位置处的元素
any indexArrayList(ArrayList *list, int index);

#endif //LINUXC_DEMO_ARRAYLIST_H
