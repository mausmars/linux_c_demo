//
// Created by root on 1/16/20.
//

#ifndef DEMO_LINUXC_NET_SERVICE_EPOLL_H
#define DEMO_LINUXC_NET_SERVICE_EPOLL_H

#include <assert.h>
#include <netinet/in.h>
#include "common.h"

typedef enum {
    ST_Stop = 0,
    ST_Init = 1,
    ST_Runing = 2
} NetServerStateType;

/**
        选项              间隔      关闭方式  等待关闭与否
        SO_DONTLINGER   不关心     优雅         否
        SO_LINGER       零        强制         否
        SO_LINGER       非零      优雅         是
    */
//发送数据的时，recvbuf=0 sendbuf=0 希望不经历由系统缓冲区到socket缓冲区的拷贝而影响程序的性能 ????
typedef struct {
    bool isdebug;                   //记录调试信息
    bool isreuseaddr;            // closesocket（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket
    bool istcpnodelay;           // 禁止发送合并的Nagle算法
    int recvbuf;                // 接收缓冲区
    int sendbuf;                // 发送缓冲区
    int maxevents;              //1000000 Since Linux 2.6.8, the size argument is ignored, but must be greater than zero.
    int maxdatasize;            //32*1024
    int backlog;                //10000
    int port;                   //
    in_addr_t host;             //host
    struct linger *linger;      //大致意思就是说SO_LINGER选项用来设置当调用closesocket时是否马上关闭socket
} NetServerConfig;

typedef struct {

} Session;

typedef struct {

} Handler;

//-----------------------------
typedef struct {
    NetServerConfig *config;
    NetServerStateType state;
    int epfd;
    int sockfd;
    pthread_t accept_thread;

} NetServer;

extern NetServer *createNetServer(NetServerConfig *config);

extern void startupNetServer(NetServer *service);

extern void shutdownNetServer(NetServer *service);
//-----------------------------

#endif //DEMO_LINUXC_NET_SERVICE_EPOLL_H
