//
// Created by Admin on 2021/6/15.
//

#ifndef LINUXC_DEMO_NET_UTIL_H
#define LINUXC_DEMO_NET_UTIL_H

#include "model.h"

//------------------------------
//接口
long str16Tolong(string valueStr);

//比较字符串
bool compareStr(string str1, string str2);

//获取网卡名字
string ifaName();

//获取网关地址
u_byte *gateway();

//获取arp表信息
ArrayList *arpMap();

//---------------
void ping(string ip);

//休眠
u_int cover_sleep(u_int seconds);

//---------------
string ip2Str(u_byte *ipv4);

string mac2Str(u_byte *mac);
//---------------
#endif //LINUXC_DEMO_NET_UTIL_H
