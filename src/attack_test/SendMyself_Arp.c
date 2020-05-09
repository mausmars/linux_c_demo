/*
 This   program   sends   out   ARP   packet(s)   with   source/target   IP
 and   Ethernet   hardware   addresses   supplied   by   the   user.
 */
#include   <stdlib.h>
#include   <netdb.h>
#include   <sys/socket.h>
#include   <sys/types.h>
#include   <stdio.h>
#include   <errno.h>
#include   <sys/ioctl.h>
#include   <net/if.h>
#include   <signal.h>
#include   <netinet/ip.h>
#include   <netinet/in.h>
#include   <string.h>
#include   <arpa/inet.h>
#include   <netinet/ip_icmp.h>
#include   <linux/if_ether.h>

#define   ETH_HW_ADDR_LEN   6
#define   IP_ADDR_LEN   4
#define   ARP_FRAME_TYPE   0x0806
#define   ETHER_HW_TYPE   1
#define   IP_PROTO_TYPE   0x0800
#define   OP_ARP_REQUEST   2
#define   OP_ARP_QUEST   1
#define   DEFAULT_DEVICE   "eth0"

struct arp_packet {
    //以太网首部
    u_char targ_hw_addr[6]; //广播mac地址
    u_char src_hw_addr[6]; //源mac地址
    u_short frame_type; //帧类型

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

void die(char *);
void get_ip_addr(struct in_addr *, char *);
void get_hw_addr(char *, char *);

int main(int argc, char * argv[]) {
    struct arp_packet pkt;
    bzero(&pkt, 42);
    show("init");
    struct in_addr src_in_addr, targ_in_addr;

    struct sockaddr sa;
    int sock;
    int j, number;
    //	show(usage);
    sock = socket(AF_INET, SOCK_PACKET, htons(ETH_P_RARP));
    if (sock < 0) {
        perror("socket");
        exit(1);
    } else {
        show("sock created !");
    }
    //number=atoi(1);
    number = 1;

    show("yitaiwang tou ");
    //以太网首部
    get_hw_addr(pkt.targ_hw_addr, "ff:ff:ff:ff:ff:ff"); //广播mac地址
    get_hw_addr(pkt.src_hw_addr, "00:19:5b:74:27:3b"); //源mac地址
    pkt.frame_type = htons(0x0806); //帧类型 ARP_FRAME_TYPE

    show("arp tou");
    //28字节arp请求 应答
    pkt.hw_type = htons(0x0001); //硬件类型
    pkt.prot_type = htons(0x0800); //协议类型
    pkt.hw_addr_size = 6; //硬件地址长度
    pkt.prot_addr_size = 4; //协议地址长度
    pkt.op = htons(0x0001); //操作类型    OP_ARP_QUEST 1  OP_ARP_REQUEST 2
    get_hw_addr(pkt.sndr_hw_addr, "00:19:5b:74:27:3b"); //发送端源mac地址 00:1D:7D:45:1C:09
    get_hw_addr(pkt.rcpt_hw_addr, "00:00:00:00:00:00"); //目的mac地址
    get_ip_addr(&src_in_addr, "192.168.0.199"); //发送端源ip地址
    get_ip_addr(&targ_in_addr, "192.168.0.182"); //目的ip地址

    memcpy(pkt.sndr_ip_addr, &src_in_addr, 4);
    memcpy(pkt.rcpt_ip_addr, &targ_in_addr, 4);
    bzero(pkt.padding, 18);
    strcpy(sa.sa_data, "192.168.0.182");

    show("send start!");
    for (j = 0; j < number; j++) {
        if (sendto(sock, &pkt, sizeof(pkt), 0, &sa, sizeof(sa)) < 0) {
            perror("sendto");
            exit(1);
        } else {
            printf("%s\n", "sendtoing");
        }
    }
    show("send finish!");
    exit(0);
}

void die(char *str) {
    fprintf(stderr,"%s\n", str);
    exit(1);
}

void show(char * str) {
    fprintf(stderr,"%s\n", str);
}

void get_ip_addr(struct in_addr *in_addr, char *str) {
    struct hostent *hostp;
    in_addr->s_addr = inet_addr(str);
    if (in_addr->s_addr == -1) {
        if ((hostp = gethostbyname(str)))
            bcopy(hostp->h_addr, in_addr, hostp->h_length);
        else {
            fprintf(stderr, "send_arp: unknown host %s\n", str);
            exit(1);
        }
    }
}

void get_hw_addr(char *buf, char *str) {
    int i;
    char c, val;
    for (i = 0; i < 6; i++) {
        if (!(c = tolower(*str++)))
            die("Invalid hardware address");
        if (isdigit(c))
            val = c - '0';
        else if (c >= 'a' && c <= 'f')
            val = c - 'a' + 10;
        else
            die("Invalid hardware address");
        *buf = val << 4;
        if (!(c = tolower(*str++)))
            die("Invalid hardware address");
        if (isdigit(c))
            val = c - '0';
        else if (c = 'a' && c <= 'f')
            val = c - 'a' + 10;
        else
            die("Invalid hardware address");
        *buf++ |= val;
        if (*str == ':')
            str++;
    }
}
