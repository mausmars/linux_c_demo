#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "net_util.h"

#define Route_Path "/proc/net/route"
#define Arp_Path "/proc/net/arp"

//----------------------------------
//字符串转int  “0x1b”
long str16Tolong(string valueStr) {
//    byte str;
    long i = strtol(valueStr, 0, 16);
    return i;
}

long strTolong(string str) {
    long i = atol(str);
    return i;
}

int strToint(string str) {
    int i = atoi(str);
    return i;
}

float strTofloat(string str) {
    float i = atof(str);
    return i;
}

//---------------------------------------------
//01134F0A
u_byte *ipSplit2(string str) {
    u_byte *ipv4 = cover_malloc(4 * sizeof(u_byte));
    for (int i = 3; i >= 0; i--) {
        byte v1[3];
        memset(&v1, 0, sizeof(v1));
        strncpy(v1, str + i * 2, 2);

        byte v[5];
        memset(&v, 0, sizeof(v));
        strcpy(v, "0x");
        strcat(v, v1);
        ipv4[3 - i] = str16Tolong(v);
    }
    return ipv4;
}

//192.168.0.1
u_byte *ipSplit(string str) {
    int index = 0;
    u_byte *ipv4 = cover_malloc(4 * sizeof(u_byte));
    for (string token = strtok(str, IpDelim); token != NULL; token = strtok(NULL, IpDelim)) {
        ipv4[index] = strToint(token);
        index++;
    }
    return ipv4;
}

//a4:bb:6d:4c:e3:49
u_byte *macSplit(string str) {
    int index = 0;
    u_byte *mac = cover_malloc(6 * sizeof(u_byte));
    for (string token = strtok(str, MacDelim); token != NULL; token = strtok(NULL, MacDelim)) {
        mac[index] = str16Tolong(token);
        index++;
    }
    return mac;
}

//---------------------------------------------
void ping(string ip) {
    if (execlp("ping", "ping", "-c", "1", ip, (byte *) 0) < 0) {
        printf("ping error\n");
        exit(1);
    }
    printf("ping over! \n");
}

void arp() {
    if (execlp("arp", "arp", "-a", (byte *) 0) < 0) {
        printf("arp -a error\n");
        exit(1);
    }
    printf("arp -a! \n");
}

string ifaName() {
    struct ifaddrs *ifa = NULL, *ifaList;

    string ifaName = "";
    if (getifaddrs(&ifaList) < 0) {
        return ifaName;
    }
    for (ifa = ifaList; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family != AF_INET) {
            continue;
        }
        if (strcmp(ifa->ifa_name, "lo") == 0) {
            continue;
        }
        ifaName = ifa->ifa_name;
        break;
    }
    //释放对象
    freeifaddrs(ifaList);
    return ifaName;
}

u_byte *gateway() {
    string path = Route_Path;
    string delim = "\t";

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("%s isn't exist! \n", path);
        return NULL;
    }
    byte line[200];
    string token;
    fgets(line, sizeof(line) - 1, fp); //跳过一行
    while (!feof(fp)) {
        memset(line, 0, sizeof(line));
        fgets(line, sizeof(line) - 1, fp); // 包含了换行符
        int index = 0;
        for (token = strtok(line, delim); token != NULL; token = strtok(NULL, delim)) {
            if (index == 2) {
                break;
            }
            index++;
        }
        break;
    }
    //关闭文件
    fclose(fp);
    //直接初始化会栈数组逃逸，使用malloc堆内存操作
    return ipSplit2(token);
}

void arpMap() {
    string path = Arp_Path;
    string delim = " ";

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("%s isn't exist! \n", path);
        return;
    }
    byte line[200];
    fgets(line, sizeof(line) - 1, fp); //跳过一行
    while (!feof(fp)) {
        memset(line, 0, sizeof(line));
        fgets(line, sizeof(line) - 1, fp); // 包含了换行符
        int index = 0;

        ArpMap *arpMap = createArpMap();
        Array *ipmac = createArray(2);
        for (string token = strtok(line, delim); token != NULL; token = strtok(NULL, delim)) {
            if (index == 0) {
                printf("%s\n", token);
                ipmac->node[0].obj = token;
            } else if (index == 3) {
                printf("%s\n", token);
                ipmac->node[1].obj = token;
            }
            index++;
        }
        arpMap->mac = macSplit(ipmac->node[0].obj);
        arpMap->ip = ipSplit(ipmac->node[1].obj);
    }
    fclose(fp);
}

void printRoute() {
    string path = Route_Path;

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("%s isn't exist! \n", path);
        return;
    }
    byte line[1000] = {0};

    //第一行读取网关
    while (!feof(fp)) {
        memset(line, 0, sizeof(line));
        fgets(line, sizeof(line) - 1, fp); // 包含了换行符
        printf("%s", line);
    }
    fclose(fp);
}

void printIfa() {
    struct sockaddr_in *sin = NULL;
    struct ifaddrs *ifa = NULL, *ifList;

    if (getifaddrs(&ifList) < 0) {
        return;
    }
    for (ifa = ifList; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family == AF_INET) {
            printf(">>> interfaceName: %s \n", ifa->ifa_name);

            sin = (struct sockaddr_in *) ifa->ifa_addr;
            printf(">>> ipAddress: %s \n", inet_ntoa(sin->sin_addr));

            sin = (struct sockaddr_in *) ifa->ifa_dstaddr;
            printf(">>> broadcast: %s \n", inet_ntoa(sin->sin_addr));

            sin = (struct sockaddr_in *) ifa->ifa_netmask;
            printf(">>> subnetMask: %s \n", inet_ntoa(sin->sin_addr));

            sin = (struct sockaddr_in *) ifa->ifa_netmask;
            printf(">>> subnetMask: %s \n", inet_ntoa(sin->sin_addr));
        }
    }
    freeifaddrs(ifList);
}

int main(int argc, char *argv[]) {
//    1.当前网卡名
//    printIfa();
//    printf("IfaName = %s", ifaName());

    //2.获取网关ip
//    u_byte *ipv4 = gateway();
//    for (int i = 0; i < 4; i++) {
//        printf("%d", *(ipv4 + i));
//        if (i == 3) {
//            printf("\n");
//        } else {
//            printf(".");
//        }
//    }

//    ping("10.79.19.1");
    arpMap();
    return 0;
}
