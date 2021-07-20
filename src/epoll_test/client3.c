/*压力测试程序**/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MaxDataSize 2*1024
#define MaxEvents 1000

#define ServerHost "127.0.0.1"
#define ServerPort 8000
#define TimeOut 2000
#define ClienCount 5

//每个客户连接不停地向服务器发送这个请求
static const char *request = "test";

static int setnonblocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

static void addfd(int epoll_fd, int fd) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLOUT | EPOLLET | EPOLLERR;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

//向服务器写入len字节的数据
static int write_nbytes(int sockfd, const char *buffer, int len) {
    int bytesWrite = 0;
    printf("write out %d bytes to socket %d \n", len, sockfd);
    while (1) {
        bytesWrite = send(sockfd, buffer, len, 0);
        if (bytesWrite == -1)
            return 0;
        else if (bytesWrite == 0)
            return 0;
        len -= bytesWrite;
        buffer = buffer + bytesWrite;
        if (len <= 0)
            return 1;
    }
}

//从服务器读取数据
static int read_once(int sockfd, char *buffer, int len) {
    int bytesRead = 0;
    memset(buffer, '\0', len);
    bytesRead = recv(sockfd, buffer, len, 0);
    if (bytesRead == -1) {
        return 0;
    } else if (bytesRead == 0) {
        return 0;
    }
    printf("read in %d bytes from socket %d with content: %s\n", bytesRead, sockfd, buffer);
    return 1;
}

// 向服务器发起num个TCP连接， 我们可以通过改变num来调整测试压力
static void start_conn(int epoll_fd, int num, const char *ip, int port) {
//    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    for (int i = 0; i < num; ++i) {
        sleep(1);
        int sockfd = socket(PF_INET, SOCK_STREAM, 0);
        printf(" create 1 sock\n");
        if (sockfd < 0)
            continue;
        if (connect(sockfd, (struct sockaddr *) &address, sizeof(address)) == 0) {
            printf(" build connection %d\n", i);
            addfd(epoll_fd, sockfd);
        }
    }
}

static void close_conn(int epoll_fd, int sockfd) {
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sockfd, 0);
    close(sockfd);
}

int main(int argc, char *argv[]) {
    int num = ClienCount;
    char *ip = ServerHost;
    int port = ServerPort;
    printf("测试连接 %s:%d 数量=%d \n", ip, port, num);

    int epoll_fd = epoll_create1(0);
    start_conn(epoll_fd, num, ip, port);
    struct epoll_event events[MaxEvents];
    char buffer[MaxDataSize];

    int a = 1;

    while (1) {
        if (a < 0) {
            break;
        }
        int fds = epoll_wait(epoll_fd, events, MaxEvents, TimeOut);
        for (int i = 0; i < fds; i++) {
            int sockfd = events[i].data.fd;
            if (events[i].events & EPOLLIN) {
                if (!read_once(sockfd, buffer, MaxDataSize)) {
                    close_conn(epoll_fd, sockfd);
                }
                struct epoll_event event;
                event.events = EPOLLOUT | EPOLLET | EPOLLERR;
                event.data.fd = sockfd;
                epoll_ctl(epoll_fd, EPOLL_CTL_MOD, sockfd, &event);
            } else if (events[i].events & EPOLLOUT) {
                if (!write_nbytes(sockfd, request, strlen(request))) {
                    close_conn(epoll_fd, sockfd);
                }
                struct epoll_event event;
                event.events = EPOLLIN | EPOLLET | EPOLLERR;
                event.data.fd = sockfd;
                epoll_ctl(epoll_fd, EPOLL_CTL_MOD, sockfd, &event);
            } else if (events[i].events & EPOLLERR) {
                close_conn(epoll_fd, sockfd);
            }
        }
    }
}
