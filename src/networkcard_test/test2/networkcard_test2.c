//
// Created by Admin on 2021/3/19.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>

// 获取本机ip  eth_inf网卡名称 调用方法get_local_ip("apcli0", ip);
int main(int argc, char **argv) {
    char *eth_inf = "eth0";

    int sd;
    struct sockaddr_in sin;
    struct ifreq ifr;

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sd) {
        printf("socket error: %s\n", strerror(errno));
        return -1;
    }

    strncpy(ifr.ifr_name, eth_inf, IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;

    // if error: No such device
    if (ioctl(sd, SIOCGIFADDR, &ifr) < 0) {
        printf("ioctl error: %s\n", strerror(errno));
        close(sd);
        return -1;
    }

    printf("interfac: %s, ip: %s\n", eth_inf, inet_ntoa(((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr));
    close(sd);
    return 0;
}