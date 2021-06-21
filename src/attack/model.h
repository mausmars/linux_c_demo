//
// Created by root on 11/18/19.
//

#ifndef ATTACK_LINUXC_MODEL_H
#define ATTACK_LINUXC_MODEL_H

#include <stdio.h>
#include <unistd.h>

#include "../common/memory.h"
#include "../common/type.h"
//#include "../common/exception.h"

#include "../common/array.h"
#include "../common/arraylist.h"
//-------------------------------
//常量
#define IpDelim "."
#define MacDelim ":"
#define SpaceDelim " "
#define TableDelim "\t"

#define Route_Path "/proc/net/route"
#define Arp_Path "/proc/net/arp"
//-------------------------------
enum StateType {
    StateType_Stop = 0,//停止
    StateType_Attack = 1,//进攻中
};

//枚举
enum EtherType {
    ETHERTYPE_IPv4 = 0x0800,
    ETHERTYPE_IPv6 = 0x86DD,
    ETHERTYPE_ARP = 0x0806,
    ETHERTYPE_RARP = 0x0835,
    ETHERTYPE_TRILL = 0x22F3,
    ETHERTYPE_L2_ISIS = 0x22F4,
    ETHERTYPE_8021Q_TAG = 0x8100,
    ETHERTYPE_NEXT_HOP_FORWARDING = 0x86FF,
    ETHERTYPE_FLOW_CONTROL = 0x8808,
    ETHERTYPE_8021ad_S_TAG = 0x88A8,
    ETHERTYPE_MPLS_UNICAST = 0x8847,
    ETHERTYPE_MPLS_MULTICAST = 0x8848,
};

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
extern string etherTypeToStr(int etherType);

extern ArpMap *createArpMap();

extern void freeArpMap(ArpMap *arpMap);

#endif //ATTACK_LINUXC_MODEL_H