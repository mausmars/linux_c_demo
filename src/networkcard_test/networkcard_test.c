//
// Created by Admin on 2021/3/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

int main(int argc, char* argv[]) {
    struct ifaddrs *ifc, *ifc1;
    char ip[64] = {};
    char nm[64] = {};

    if(0 != getifaddrs(&ifc)) return -1;
    ifc1 = ifc;

    printf("iface\tIP address\tNetmask\n");
    for (; NULL != ifc; ifc = (*ifc).ifa_next) {
        printf("%s", (*ifc).ifa_name);
        if (NULL != (*ifc).ifa_addr) {
            inet_ntop(AF_INET, &(((struct sockaddr_in*)((*ifc).ifa_addr))->sin_addr), ip, 64);
            printf("\t%s", ip);
        } else {
            printf("\t\t");
        }
        if (NULL != (*ifc).ifa_netmask) {
            inet_ntop(AF_INET, &(((struct sockaddr_in*)((*ifc).ifa_netmask))->sin_addr), nm, 64);
            printf("\t%s", nm);
        } else {
            printf("\t\t");
        }
        printf("\n");
    }

    freeifaddrs(ifc1);
    return 0;
}