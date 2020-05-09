#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h> //ip
#include <netinet/tcp.h> //tcp
#include <netinet/ip_icmp.h>
#include <stdlib.h>
#include <string.h>

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
    int i;
    int sock, bytes_send, fromlen, n, id, s;
    unsigned char buffer[8192];
    struct timeval tv;

    struct sockaddr_in toaddr;
    struct ip *ip = (struct ip *) buffer;
    struct icmp *icmp = (struct icmp *) (buffer + 20);

    long *data = (long *) icmp->icmp_data;

    bzero(buffer, 8192);
    gettimeofday(&tv, NULL);

    toaddr.sin_family = AF_INET;
    toaddr.sin_addr.s_addr = inet_addr("192.168.2.202");

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock > 0) {
        printf("socket ok\n");
    } else {
        printf("socket error \n");
    }

    n = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &n, sizeof(n)) < 0) {
        printf("2");
        perror("IP_HDRINCL");
        exit(1);
    }

    ip = (struct ip *) buffer;
    ip->ip_id = 0x9911;
    ip->ip_v = 4; //IPVERSION   版本一般的是 4
    ip->ip_hl = 5; // IP数据包的头部长度
    ip->ip_ttl = 36;
    ip->ip_p = IPPROTO_ICMP; // tcp 为6          IPPROTO_TCP、IPPROTO_UDP、IPPROTO_ICMP、IPPROTO_IGMP或者IPPROTO_IP
    ip->ip_len = htons(60);
    inet_aton("192.168.2.202", &ip->ip_dst);
    inet_aton("192.168.0.155", &ip->ip_src);
    ip->ip_sum = 0;

    icmp ->icmp_type = 8;
    icmp ->icmp_code = 0;
    icmp ->icmp_cksum = 0x0;
    icmp ->icmp_id = 0;
    icmp ->icmp_seq = 0;

    icmp ->icmp_id = getpid() & 0xffff;
    icmp ->icmp_seq = 148;

    data[0] = tv.tv_sec;
    data[1] = tv.tv_usec;

    for (i = 8; i < 64; i++)
        icmp->icmp_data[i] = (unsigned char) i;

    ip->ip_sum = csum((unsigned short *) ip, 20);
    icmp->icmp_cksum = in_cksum((unsigned short *) icmp, 52);

    int iii;

    printf("start \n");
    //	for (iii = 0; iii < 1000; iii++) {
    while (1) {
        bytes_send = sendto(sock, buffer, 72, 0, (struct sockaddr *) &toaddr, sizeof(toaddr));
        //if (bytes_send>0){
        //printf("OK bytes_send %d \n",bytes_send);
        //printf("IP_source address ::: %s \n",inet_ntoa(ip->ip_src));
        //printf("IP_dest address ::: %s \n",inet_ntoa(ip->ip_dst));
        //}
    }

    printf("over \n");
    return 0;
}
