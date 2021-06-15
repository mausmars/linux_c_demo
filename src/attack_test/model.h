//
// Created by root on 11/18/19.
//

#ifndef ATTACK_LINUXC_MODEL_H
#define ATTACK_LINUXC_MODEL_H

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

char *etherTypeToStr(int etherType) {
    char *et = "";
    switch (etherType) {
        case 0x0800:
            et = "ETHERTYPE_IPv4";
            break;
        case 0x86DD:
            et = "ETHERTYPE_IPv6";
            break;
        case 0x0806:
            et = "ETHERTYPE_ARP";
            break;
        case 0x0835:
            et = "ETHERTYPE_RARP";
            break;
        case 0x22F3:
            et = "ETHERTYPE_TRILL";
            break;
        case 0x22F4:
            et = "ETHERTYPE_L2_ISIS";
            break;
        case 0x8100:
            et = "ETHERTYPE_8021Q_TAG";
            break;
        case 0x86FF:
            et = "ETHERTYPE_NEXT_HOP_FORWARDING";
            break;
        case 0x8808:
            et = "ETHERTYPE_FLOW_CONTROL";
            break;
        case 0x88A8:
            et = "ETHERTYPE_8021ad_S_TAG";
            break;
        case 0x8847:
            et = "ETHERTYPE_MPLS_UNICAST";
            break;
        case 0x8848:
            et = "ETHERTYPE_MPLS_MULTICAST";
            break;
        default:
            et = "Other!";
            printf("Other! 0x%2x \n", etherType);
            break;
    }
    return et;
}


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

#endif //ATTACK_LINUXC_MODEL_H
