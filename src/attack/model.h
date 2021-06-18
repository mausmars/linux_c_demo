//
// Created by root on 11/18/19.
//

#ifndef ATTACK_LINUXC_MODEL_H
#define ATTACK_LINUXC_MODEL_H

#include "memory_mgr.h"

//-------------------------------
typedef char byte;
typedef unsigned char u_byte;
typedef long long l_long;
typedef long double l_double;

typedef char *string;

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
typedef struct arp {
    //28字节arp请求 应答
    u_short hw_type; //硬件类型
    u_short prot_type; //协议类型
    u_char hw_addr_size; //硬件地址长度
    u_char prot_addr_size; //协议地址长度
    u_short op; //操作类型
    u_char sndr_hw_addr[6]; //发送端源mac地址
    u_char sndr_ip_addr[4]; //发送端源ip地址
    u_char rcpt_hw_addr[6]; //目的mac地址
    u_char rcpt_ip_addr[4]; //目的ip地址
    u_char padding[18];
};

typedef struct {
    int threadId;
    int *count
} AhreadParam;

typedef struct {
    u_byte *ip;        //ip 地址
    u_byte *mac;       //mac 地址
} ArpMap;

//--------------------------
//接口
string etherTypeToStr(int etherType);

ArpMap *createArpMap();

void freeArpMap(ArpMap *arpMap);
//--------------------------

#endif //ATTACK_LINUXC_MODEL_H