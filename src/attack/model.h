//
// Created by root on 11/18/19.
//

#ifndef ATTACK_LINUXC_MODEL_H
#define ATTACK_LINUXC_MODEL_H

#include "memory_mgr.h"

//-------------------------------
//变量类型
typedef char byte;
typedef unsigned char u_byte;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

typedef long long l_long;
typedef long double l_double;

typedef char *string;
typedef void *any;

//-------------------------------
//常量
#define IpDelim "."
#define MacDelim ":"

//-------------------------------
//枚举
//EtherType
#define ETHERTYPE_IPv4 0x0800
#define ETHERTYPE_IPv6 0x86DD
#define ETHERTYPE_ARP 0x0806
#define ETHERTYPE_RARP 0x0835
#define ETHERTYPE_TRILL 0x22F3
#define ETHERTYPE_L2_ISIS 0x22F4
#define ETHERTYPE_8021Q_TAG 0x8100
#define ETHERTYPE_NEXT_HOP_FORWARDING 0x86FF
#define ETHERTYPE_FLOW_CONTROL 0x8808
#define ETHERTYPE_8021ad_S_TAG 0x88A8
#define ETHERTYPE_MPLS_UNICAST 0x8847
#define ETHERTYPE_MPLS_MULTICAST 0x8848

//-----------------------------
typedef struct {
    //28字节arp请求 应答
    u_short hw_type; //硬件类型
    u_short prot_type; //协议类型
    u_byte hw_addr_size; //硬件地址长度
    u_byte prot_addr_size; //协议地址长度
    u_short op; //操作类型
    u_byte sndr_hw_addr[6]; //发送端源mac地址
    u_byte sndr_ip_addr[4]; //发送端源ip地址
    u_byte rcpt_hw_addr[6]; //目的mac地址
    u_byte rcpt_ip_addr[4]; //目的ip地址
    u_byte padding[18];
} Arp;

typedef struct {
    int threadId;
    int *count;
} AthreadParam;
//--------------------------
typedef struct {
    u_byte *ip;        //ip 地址
    u_byte *mac;       //mac 地址
} ArpMap;

//-------------------------------
//数组类型
typedef struct {
    void *obj;
} Node;

typedef struct {
    int size;
    Node *node;
} Array;

extern string etherTypeToStr(int etherType);

extern ArpMap *createArpMap();

extern void freeArpMap(ArpMap *arpMap);

extern Array *createArray(int size);

extern void *getArrayByIndex(Array *array, int index);

#endif //ATTACK_LINUXC_MODEL_H