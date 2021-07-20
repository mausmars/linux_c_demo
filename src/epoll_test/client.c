#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <netinet/tcp.h>
#include <pthread.h>

#define MaxDataSize 32*1024
#define ServerHost "127.0.0.1"
#define ServerPort 8000

static int set_sockeopt(int sockfd) {
    //level 选项定义的层次;目前仅支持 SOL_SOCKET 和 IPPROTO_TCP 层次
    int is_debug = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_DEBUG, (const void *) &(is_debug), sizeof(int)) == -1) {
        //记录调试信息
        perror("setsockopt SO_DEBUG error!");
        return -1;
    }
    int is_reuseaddr = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &(is_reuseaddr), sizeof(int)) == -1) {
        //closesocket（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket
        perror("setsockopt SO_REUSEADDR error!");
        return -1;
    }
    /**
        选项              间隔      关闭方式  等待关闭与否
        SO_DONTLINGER   不关心     优雅         否
        SO_LINGER       零        强制         否
        SO_LINGER       非零      优雅         是
    */
    struct linger linger;
    linger.l_onoff = 1;//(在closesocket()调用,但是还有数据没发送完毕的时候容许逗留 如果m_sLinger.l_onoff=0;则功能和2作用相同
    linger.l_linger = 5;//(容许逗留的时间为5秒)
    if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (const void *) &(linger), sizeof(struct linger)) == -1) {
        //大致意思就是说SO_LINGER选项用来设置当调用closesocket时是否马上关闭socket
        perror("setsockopt SO_LINGER error!");
        return -1;
    }
    //发送数据的时，希望不经历由系统缓冲区到socket缓冲区的拷贝而影响程序的性能
//    int zero=0;
//    setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(const void *)&zero,sizeof(zero));
//    setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(const void *)&zero,sizeof(zero));
    int recvbuf = 32 * 1024;//设置为32K
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (const void *) &recvbuf, sizeof(int)) == -1) {
        // 接收缓冲区
        perror("setsockopt SO_RCVBUF error!");
        return -1;
    }
    int sendbuf = 32 * 1024;//设置为32K
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (const void *) &sendbuf, sizeof(int)) == -1) {
        //发送缓冲区
        perror("setsockopt SO_SNDBUF error!");
        return -1;
    }

    //SO_CONDITIONAL_ACCEPT ???
//    if (setsockopt(sockfd, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (const void *) &sendbuf, sizeof(int)) == -1) {

    int is_tcpnodelay = 1;
    if (setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (const void *) &(is_tcpnodelay), sizeof(int)) == -1) {
        //禁止发送合并的Nagle算法
        perror("setsockopt TCP_NODELAY error!");
        return -1;
    }
    return 0;
}

static int testclient() {
    char buf[MaxDataSize];
    int sockfd, numbytes;
    struct sockaddr_in server_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        return 1;
    }
    if (set_sockeopt(sockfd) == -1) {
        perror("set_sockeopt error!!!");
        return -1;
    }
    memset(&server_addr, 0, sizeof(struct sockaddr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(ServerPort);
    server_addr.sin_addr.s_addr = inet_addr(ServerHost);
    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect error");
        return 1;
    }
//    printf("send: Hello, world!\n");
    if (send(sockfd, "Hello, world!", 14, 0) == -1) {
        perror("send error");
        return 1;
    }
    if ((numbytes = recv(sockfd, buf, MaxDataSize, 0)) == -1) {
        perror("recv error");
        return 1;
    }
    if (numbytes) {
        buf[numbytes] = '\0';
//        printf("received: %s\n", buf);
    }
    close(sockfd);
}

//批量发送
static void clientSend() {
    printf("clientSend\n");
    for (int i = 0; i < 100; i++) {
        testclient();
    }
}

int main(int argc, char *argv[]) {
    int threadCount = 100;

    for (int k = 0; k < threadCount; k++) {
        printf("启动线程: %d\n", k);
        pthread_t thread;
        pthread_create(&thread, NULL, &clientSend, NULL);
        pthread_join(thread, NULL);
    }
    return 0;
}
