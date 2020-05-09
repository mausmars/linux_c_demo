#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

#define MaxDataSize 32*1024
#define BackLog 10000
#define MaxEvents 1000000 // Since Linux 2.6.8, the size argument is ignored, but must be greater than zero.
#define ServerPort 8000

struct sockaddr_in server_addr;
struct sockaddr_in client_addr;

static int socket_non_blocking(int sockfd) {
    int flags, s;

    flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl(sockfd, F_SETFL, flags);
    if (s == -1) {
        perror("fcntl");
        return -1;
    }
    return 0;
}

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
    int is_tcpnodelay = 1;
    if (setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (const void *) &(is_tcpnodelay), sizeof(int)) == -1) {
        //禁止发送合并的Nagle算法
        perror("setsockopt TCP_NODELAY error!");
        return -1;
    }
    return 0;
}

static int create_and_bind(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error!!!");
        return -1;
    }
    if (set_sockeopt(sockfd) == -1) {
        perror("set_sockeopt error!!!");
        return -1;
    }
    memset(&client_addr, 0, sizeof(struct sockaddr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind error");
        close(sockfd);
        return -1;
    }
    return sockfd;
}

int main(int argc, char *argv[]) {
    // 数据缓存区域
    char buf[MaxDataSize];

    // 检查是否指定端口
//	if (argc != 2) {
//		fprintf(stderr, "Usage: %d [port]\n", SERV_PORT);
//		exit(EXIT_FAILURE);
//	}
//	char *port_argv = argv[1];
//	int port = atoi(port_argv);
    int port = ServerPort;

    // 创建并监听tcp socket
    int sockfd = create_and_bind(port);
    if (sockfd == -1)
        abort();

    // 设置socket为非阻塞
    if (socket_non_blocking(sockfd) == -1)
        abort();

    // 创建epoll句柄
    int epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create error");
        abort();
    }

    // epoll_ctl
    struct epoll_event event;
    event.data.fd = sockfd;
    event.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event) == -1) {
        perror("epoll_ctl error");
        abort();
    }

    /* Buffer where events are returned */
    struct epoll_event *events;
    events = calloc(MaxEvents, sizeof event);

    // listen
    if (listen(sockfd, BackLog) == -1) {
        perror("listen error");
        abort();
    }

    /* I/O复用的模型 */
    while (1) {
        int n, i, new_fd, numbytes;
        n = epoll_wait(epfd, events, MaxEvents, -1);
        for (i = 0; i < n; i++) {
            /* We have a notification on the listening socket, which
             means one or more incoming connections. */
            if (events[i].data.fd == sockfd) {
                // accept 有新的连接
                int sin_size = sizeof(struct sockaddr_in);
                if ((new_fd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size)) == -1) {
                    perror("accept error");
                    continue;
                }
                printf("server: got connection from %s\n", inet_ntoa(client_addr.sin_addr));

                // epoll_ctl
                event.data.fd = new_fd;
                //EPOLLIN 连接到达；有数据来临；
                //EPOLLET 边缘触发
                event.events = EPOLLIN | EPOLLET;
                //将新的fd添加到epoll的监听队列中
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, new_fd, &event) == -1) {
                    perror("epoll_ctl error");
                    abort();
                }
            } else if (events[i].events & EPOLLIN) {
                //接收到数据，读socket
                if ((new_fd = events[i].data.fd) < 0)
                    continue;

                if ((numbytes = read(new_fd, buf, MaxDataSize)) < 0) {
                    if (errno == ECONNRESET) {
                        close(new_fd);
                        events[i].data.fd = -1;
                        epoll_ctl(epfd, EPOLL_CTL_DEL, new_fd, &event);
                    } else {
                        printf("readline error");
                    }
                } else if (numbytes == 0) {
                    close(new_fd);
                    events[i].data.fd = -1;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, new_fd, &event);
                } else {
                    // numbytes > 0
                    printf("received data: %s\n", buf);
                }
                event.data.fd = new_fd;
                event.events = EPOLLOUT | EPOLLET;
                //修改标识符，等待下一个循环时发送数据，异步处理的精髓
                epoll_ctl(epfd, EPOLL_CTL_MOD, new_fd, &event);
            } else if (events[i].events & EPOLLOUT) {
                //有数据待发送，写socket
                new_fd = events[i].data.fd;
                write(new_fd, buf, numbytes);//发送数据

                printf("written data: %s\n", buf);
                printf("written numbytes: %d\n", numbytes);

                event.data.fd = new_fd;
                event.events = EPOLLIN | EPOLLET;
                //修改标识符，等待下一个循环时接收数据
                epoll_ctl(epfd, EPOLL_CTL_MOD, new_fd, &event);
            } else if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)) {
                /* An error has occured on this fd, or the socket is not
                 ready for reading (why were we notified then?) */
                fprintf(stderr, "epoll error\n");
                new_fd = events[i].data.fd;
                close(new_fd);
                events[i].data.fd = -1;
                epoll_ctl(epfd, EPOLL_CTL_DEL, new_fd, &event);
                continue;
            }
        }
    }
}

