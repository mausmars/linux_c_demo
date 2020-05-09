#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/ip_icmp.h>

#include "model.h"

#define BUFFER_MAX 4096

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

int main(int argc, char *argv[]) {
    int readnum;
    char buffer[BUFFER_MAX];
    char *otherhead;
    struct ethhdr *ethhead;
    struct arp *arppacket;
    struct icmp *icmphead;
    struct iphdr *iphead;
    struct tcphdr *tcphead;

    int num = 0;

    int sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));

    while (num < 1) {
        readnum = recvfrom(sock, buffer, BUFFER_MAX, 0, NULL, NULL);

        if (readnum < 42) {
            fprintf(stdout, "Incomplete header, packet corrupt\n");
            continue;
        }
        ethhead = buffer;
        printf("mac source:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n", ethhead->h_source[0], ethhead->h_source[1],
               ethhead->h_source[2], ethhead->h_source[3], ethhead->h_source[4], ethhead->h_source[5]);
        printf("mac dest:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n", ethhead->h_dest[0], ethhead->h_dest[1],
               ethhead->h_dest[2], ethhead->h_dest[3], ethhead->h_dest[4], ethhead->h_dest[5]);
        printf("proto:0x%2x \n", ntohs(ethhead->h_proto));

        //ip:0800,arp:0x0806,rarp:0x0835
        switch (ntohs(ethhead->h_proto)) {
            case 0x0800:
                iphead = buffer + sizeof(struct ethhdr);
                break;
            case 0x0806:
                arppacket = buffer + sizeof(struct ethhdr);
                break;
            default:
                break;
        }
    }
}
