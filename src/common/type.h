//
// Created by Admin on 2021/6/20.
//

#ifndef LINUXC_DEMO_TYPE_H
#define LINUXC_DEMO_TYPE_H

#include <stddef.h>

/**
 * 32位编译器：
 * char*（即指针变量）: 4个字节（32位的寻址空间是2^32, 即32个bit，也就是4个字节。同理64位编译器）
 * long:   4个字节
 * unsigned long:  4个字节
 * long long:  8个字节
 *
 * 64位编译器：
 * char*(即指针变量): 8个字节
 * long:   8个字节
 * unsigned long:  8个字节
 * long long:  8个字节
 */

//变量类型
typedef char byte;
typedef unsigned char u_byte;

typedef long long l_long;   //（32位系统 8字节，64位系统 8字节）
typedef long double l_double;

typedef char bool;
#define true 1
#define false 0

typedef char *string;
typedef void *any;

typedef char *pointer; //指针类型（32位系统 4字节，64位系统 8字节）

#endif //LINUXC_DEMO_TYPE_H
