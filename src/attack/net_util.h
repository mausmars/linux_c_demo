//
// Created by Admin on 2021/6/15.
//

#ifndef LINUXC_DEMO_NET_UTIL_H
#define LINUXC_DEMO_NET_UTIL_H

#include "model.h"

//------------------------------
//接口
//获取网卡名字
string ifaName();

//打印网卡信息
void printIfa();

//获取网关地址
u_byte *gateway();

//打印网关信息
void printRoute();

#endif //LINUXC_DEMO_NET_UTIL_H
