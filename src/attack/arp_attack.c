//
// Created by Admin on 2021/6/15.
//
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>

#include "net_util.h"
#include "arp_attack.h"

void arpAttack(string targetIp) {
    //获取网卡名
//    char ifaname = ifaName();

    //获取网关地址
//    int *ipv4 = gateway();

    //通过ip获取mac

}
