#include "net_server_epoll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

struct sockaddr_in server_addr;
struct sockaddr_in client_addr;

NetServerConfig *createDefaultNetServerConfig() {
    NetServerConfig *config = (NetServerConfig *) malloc(sizeof(NetServerConfig));
    config->isdebug = true;
    config->isreuseaddr = true;
    config->istcpnodelay = false;
    config->recvbuf = 32 * 1024;
    config->sendbuf = 32 * 1024;
    config->maxevents = 1000000;
    config->maxdatasize = 32 * 1024;
    config->backlog = 10000;
    config->port = 8000;
    config->host = INADDR_ANY;

    struct linger linger;
    linger.l_onoff = 1;//(在closesocket()调用,但是还有数据没发送完毕的时候容许逗留 如果m_sLinger.l_onoff=0;则功能和2作用相同
    linger.l_linger = 5;//(容许逗留的时间为5秒)
    config->linger = &linger;
    return config;
}

NetServer *createNetServer(NetServerConfig *config) {
    NetServer *server = (NetServer *) malloc(sizeof(NetServer));
    assert(server != NULL);
    if (config == NULL) {
        server->config = createDefaultNetServerConfig();
    } else {
        server->config = config;
    }
    server->state = ST_Stop;
    return server;
}

static int socket_non_blocking(NetServer *server) {
    int flags, s;
    flags = fcntl(server->sockfd, F_GETFL, 0);
    if (flags == ErrorReturn) {
        perror("fcntl");
        return ErrorReturn;
    }

    flags |= O_NONBLOCK;
    s = fcntl(server->sockfd, F_SETFL, flags);
    if (s == ErrorReturn) {
        perror("fcntl");
        return ErrorReturn;
    }
    return 0;
}

static int set_sockeopt(NetServer *server) {
    //level 选项定义的层次;目前仅支持 SOL_SOCKET 和 IPPROTO_TCP 层次
    if (setsockopt(server->sockfd, SOL_SOCKET, SO_DEBUG, &(server->config->isdebug), sizeof(int)) == ErrorReturn) {
        perror("setsockopt SO_DEBUG error!");
        return ErrorReturn;
    }
    if (setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, &(server->config->isreuseaddr), sizeof(int)) ==
        ErrorReturn) {
        perror("setsockopt SO_REUSEADDR error!");
        return ErrorReturn;
    }
    if (setsockopt(server->sockfd, SOL_SOCKET, SO_LINGER, server->config->linger, sizeof(struct linger)) ==
        ErrorReturn) {
        perror("setsockopt SO_LINGER error!");
        return ErrorReturn;
    }
    if (setsockopt(server->sockfd, SOL_SOCKET, SO_RCVBUF, &(server->config->recvbuf), sizeof(int)) == ErrorReturn) {
        perror("setsockopt SO_RCVBUF error!");
        return ErrorReturn;
    }
    if (setsockopt(server->sockfd, SOL_SOCKET, SO_SNDBUF, &(server->config->sendbuf), sizeof(int)) == ErrorReturn) {
        perror("setsockopt SO_SNDBUF error!");
        return ErrorReturn;
    }
    if (setsockopt(server->sockfd, IPPROTO_TCP, TCP_NODELAY, &(server->config->istcpnodelay), sizeof(int)) ==
        ErrorReturn) {
        perror("setsockopt TCP_NODELAY error!");
        return ErrorReturn;
    }
    return 0;
}

static int create_and_bind(NetServer *server) {
    if ((server->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == ErrorReturn) {
        perror("socket error!!!");
        return ErrorReturn;
    }
    if (set_sockeopt(server) == ErrorReturn) {
        perror("set_sockeopt error!!!");
        return ErrorReturn;
    }
    memset(&client_addr, 0, sizeof(struct sockaddr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server->config->port);
    server_addr.sin_addr.s_addr = server->config->host;
    if (bind(server->sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == ErrorReturn) {
        perror("bind error");
        close(server->sockfd);
        return ErrorReturn;
    }
    return server->sockfd;
}

void startupNetServer(NetServer *server) {
    assert(server->state == ST_Stop);
    server->state = ST_Init;

    // 创建并监听tcp socket
    int sockfd = create_and_bind(server);
    if (sockfd == ErrorReturn) {
        abort();
    }
    server->sockfd = sockfd;
    // 设置socket为非阻塞
    if (socket_non_blocking(server) == ErrorReturn) {
        abort();
    }
    // 创建epoll句柄
    int epfd = epoll_create1(0);
    if (epfd == ErrorReturn) {
        perror("epoll_create error");
        abort();
    }
    server->sockfd = sockfd;
    // epoll_ctl
    struct epoll_event event;
    event.data.fd = sockfd;
    event.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event) == ErrorReturn) {
        perror("epoll_ctl error");
        abort();
    }
    /* Buffer where events are returned */
    struct epoll_event *events;
    events = calloc(server->config->maxevents, sizeof event);
    // listen
    if (listen(sockfd, server->config->backlog) == ErrorReturn) {
        perror("listen error");
        abort();
    }
    // 数据缓存区域
    char buf[server->config->maxdatasize];

    server->state = ST_Runing;
    printf("server start!!! port=%d", server->config->port);
    /* I/O复用的模型 */
    while (server->state == ST_Runing) {
        int n, i, new_fd, numbytes;
        n = epoll_wait(epfd, events, server->config->backlog, -1);
        for (i = 0; i < n; i++) {
            /* We have a notification on the listening socket, which
             means one or more incoming connections. */
            if (events[i].data.fd == sockfd) {
                // accept 有新的连接
                int sin_size = sizeof(struct sockaddr_in);
                if ((new_fd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size)) == ErrorReturn) {
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
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, new_fd, &event) == ErrorReturn) {
                    perror("epoll_ctl error");
                    abort();
                }
            } else if (events[i].events & EPOLLIN) {
                //接收到数据，读socket
                if ((new_fd = events[i].data.fd) < 0)
                    continue;

                if ((numbytes = read(new_fd, buf, server->config->maxdatasize)) < 0) {
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

void shutdownNetServer(NetServer *server) {
    printf("server stop!!! port=%d", server->config->port);
    server->state = ST_Stop;
    close(server->epfd);
    close(server->sockfd);
}
