//
// Created by root on 11/18/19.
//

#ifndef ATTACK_LINUXC_MODEL_H
#define ATTACK_LINUXC_MODEL_H

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

#endif //ATTACK_LINUXC_MODEL_H
