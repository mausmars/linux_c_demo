#include <ctype.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>
#include<unistd.h>
#include <netinet/ip_icmp.h>

#include "../attack/model.h"

#define BUFFER_MAX 4096

//函数声明
static void printEthhead(struct ethhdr *ethhead);
//static void ipv4Handle();

int main(int argc, char *argv[]) {
    int readnum;
    uint8_t buffer[BUFFER_MAX];
    char *otherhead;
    struct ethhdr *ethhead;
    struct arp *arppacket;
    struct icmp *icmphead;
    struct iphdr *iphead;
    struct tcphdr *tcphead;

    int num = 0;
    int sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    while (num < 1) {
        readnum = recvfrom(sock, buffer, BUFFER_MAX, 0, NULL, NULL);
        if (readnum < 42) {
            fprintf(stdout, "Incomplete header, packet corrupt\n");
            continue;
        }
        ethhead = buffer;
        //ip:0800,arp:0x0806,rarp:0x0835
        switch (ntohs(ethhead->h_proto)) {
            case ETHERTYPE_IPv4:
//                printEthhead(ethhead);
//                iphead = buffer + sizeof(struct ethhdr);
//                ipv4Handle();
                break;
            case ETHERTYPE_ARP:
                printEthhead(ethhead);
//                arppacket = buffer + sizeof(struct ethhdr);
                break;
            case ETHERTYPE_RARP:
                printEthhead(ethhead);
                break;
            case ETHERTYPE_IPv6:
//                printEthhead(ethhead);
                break;
            default:
//                printEthhead(ethhead);
                break;
        }
    }
}

static void printEthhead(struct ethhdr *ethhead) {
    printf("-------------------------------------------- \n");
    printf("mac source:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n", ethhead->h_source[0], ethhead->h_source[1],
           ethhead->h_source[2], ethhead->h_source[3], ethhead->h_source[4], ethhead->h_source[5]);
    printf("mac dest:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n", ethhead->h_dest[0], ethhead->h_dest[1],
           ethhead->h_dest[2], ethhead->h_dest[3], ethhead->h_dest[4], ethhead->h_dest[5]);

    int etherType = ntohs(ethhead->h_proto);
    printf("proto:0x%2x %s \n", etherType, etherTypeToStr(etherType));
}

/*
 int open_fd(int fd) {
 int s;
 struct ifreq ifr;
 //接口名
 strcpy(ifr.ifr_name,"eth0");
 //获取接口标志
 if ((s = ioctl(fd, SIOCGIFFLAGS, &ifr)) < 0) {
 close(fd);
 return (-1);
 }
 //设置接口为混杂模式
 ifr.ifru_flags |= 0x100;  // 关闭  ifr.ifr_flags &= ~IFF_PROMISC;
 //设置接口标志
 if ((s = ioctl(fd, SIOCSIFFLAGS, &ifr)) < 0) {
 return (-1);
 }
 printf("Setting   interface   :::   %s   :::   to   promisc\n\n", intf);
 return (fd);
 }
 */