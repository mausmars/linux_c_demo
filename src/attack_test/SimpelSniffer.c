#include <ctype.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/file.h>
#include <netinet/if_ether.h>

#include<unistd.h>

#define BUFFER_MAX 4096

int main(int argc, char *argv[]) {
    int sock, readnum, proto;
    char buffer[BUFFER_MAX];
    char *ethhead, *iphead, *otherhead;

    int num = 0;

    sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));

    while (num < 1) {
        readnum = recvfrom(sock, buffer, BUFFER_MAX, 0, NULL, NULL);

        if(readnum < 42) {
            fprintf(stdout, "Incomplete header, packet corrupt\n");
            continue;
        }
        ethhead = buffer;
        iphead = ethhead + 14;
        otherhead = iphead + 20;

        int sip=iphead[15]&0XFF;
        int dip=iphead[19]&0XFF;
        if(sip!=109 && dip!=109) {
            continue;
        }

        num++;
        printf("%d--------------------------------------------------------------------\n",num);
        printf("==ethernet==\n");
        printf("MAC: %.2X:%02X:%02X:%02X:%02X:%02X==>%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
               ethhead[6]&0XFF, ethhead[7]&0XFF, ethhead[8]&0XFF, ethhead[9]&0XFF, ethhead[10]&0XFF, ethhead[11]&0XFF,
               ethhead[0]&0XFF, ethhead[1]&0XFF, ethhead[2]&0XFF,ethhead[3]&0XFF, ethhead[4]&0XFF, ethhead[5]&0XFF);
        printf("Type 0x%.2X%.2X\n",ethhead[12]&0XFF,ethhead[13]&0XFF);

        printf("==ip==\n");
        printf("vsersion:%d\n",(iphead[0]&0XFF >> 4));
        printf("head length:%d\n",(iphead[0]&0X0F));
        printf("tos:%.2X\n",iphead[1]);
        printf("all length:%u\n",(iphead[2]<<8)&0XFF00 | iphead[3]&0XFF);
        printf("ID:%u\n",(iphead[4]<<8)&0XFF00 | iphead[5]&0XFF);
        printf("flay:%d\n",(iphead[6]>>5));
        printf("off:0x%.2X%.2X\n",(iphead[6]&0X1F),iphead[7]);
        printf("tll:%d\n",iphead[8]);
        printf("protoType:%d\n",iphead[9]);
        printf("cheaknum:%u\n",(iphead[10]<<8)&0XFF00 | iphead[11]&0XFF);
        printf("IP: %d.%d.%d.%d => %d.%d.%d.%d\n",
               iphead[12]&0XFF, iphead[13]&0XFF, iphead[14]&0XFF, iphead[15]&0XFF,
               iphead[16]&0XFF, iphead[17]&0XFF, iphead[18]&0XFF, iphead[19]&0XFF);

        printf("### Protocol: ### \n");
        switch(iphead[9]) {
            case IPPROTO_ICMP:
                printf("===ICMP===\n");
                break;
            case IPPROTO_IGMP:
                printf("===IGMP===\n");
                break;
            case IPPROTO_IPIP:
                printf("===IPIP===\n");
                break;
            case IPPROTO_TCP :
                printf("===TCP===\n");
                printf("source port: %u,",(otherhead[0]<<8)&0XFF00 | otherhead[1]&0XFF);
                printf("dest port: %u\n", (otherhead[2]<<8)&0XFF00 | otherhead[3]&0XFF);
                break;
            case IPPROTO_UDP :
                printf("===UDP\n===");
                printf("source port: %u,",(otherhead[0]<<8)&0XFF00 | otherhead[1]&0XFF);
                printf("dest port: %u\n", (otherhead[2]<<8)&0XFF00 | otherhead[3]&0XFF);
                break;
            case IPPROTO_RAW :
                printf("===RAW\n===");
                break;
            default:
                printf("Unkown, please query in include/linux/in.h\n");
        }

        int fd1;
        fd1 = open("packet", O_CREAT| O_RDWR, 0777); //O_CREAT 若欲打开的文件不存在则自动建立该文件 .  O_RDWR 以可读写方式打开文件
        if (fd1 < 0) {
            perror("Cannot create the test file");
            return 1;
        }
        write(fd1,buffer,BUFFER_MAX);
        close(fd1);
    }
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