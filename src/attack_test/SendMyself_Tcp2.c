#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h> //ip
#include <netinet/tcp.h> //tcp
#include <stdlib.h>

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

int main() {
    int sock, bytes_send, fromlen, n, id, s;

    struct sockaddr_in toaddr;
    struct ip *iphead;
    struct tcphdr *tcphead;

    unsigned char buffer[65535];
    for (n = 0; n < 60000; n++) {
        buffer[n] = 0;
    }

    toaddr.sin_family = AF_INET;
    toaddr.sin_addr.s_addr = inet_addr("192.168.0.182");
    // inet_aton("192.168.0.182",&toaddr.sin_addr); //字符串转入

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

    iphead = (struct ip *) buffer;
    iphead->ip_id = 0x9911;
    iphead->ip_v = 4;
    iphead->ip_hl = 5;
    iphead->ip_ttl = 36;
    iphead->ip_p = 6; //tcp 为6
    iphead->ip_len = htons(60);
    //inet_aton(dstip,&ip->ip_dst);
    inet_aton("192.168.0.182", &iphead->ip_dst);

    tcphead = (struct tcphdr *) (buffer + (4 * iphead->ip_hl));
    tcphead->source = htons(12345); //源端口
    tcphead->dest = htons(80);
    tcphead->seq = htons(0x9990);
    tcphead-> syn = 1;
    tcphead-> urg = 1;
//	tcp->doff = 0x15;
    tcphead->ack_seq = 0;
    tcphead->window = htons(0x20);
    inet_aton("192.168.0.188", &iphead->ip_src);

    tcphead->check = tcpcsum((unsigned char *) buffer, (unsigned short *) tcphead, 40);
    iphead->ip_sum = csum((unsigned short *) buffer, 20);

    int j;
    for (j = 0; j < 1000; j++) {
        bytes_send = sendto(sock, buffer, 60, 0, (struct sockaddr *) &toaddr, sizeof(toaddr));
    }

    //	if (bytes_send > 0) {
    //		printf("OK bytes_send %d \n", bytes_send);
    //		printf("IP_source address ::: %s \n", inet_ntoa(ip->ip_src));
    //		printf("IP_dest address ::: %s \n", inet_ntoa(ip->ip_dst));
    //	}

    return 0;
}
