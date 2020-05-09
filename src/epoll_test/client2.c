#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>

#define BUFSIZE 666
#define SERV_PORT 8000
#define OPEN_MAX 1024

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[BUFSIZE];
    int sockfd, n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);

    /*连接服务端*/
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    while(fgets(buf, BUFSIZE, stdin) != NULL){
        /*通过sockfd给服务端发送数据*/
        write(sockfd, buf, strlen(buf));
        n = read(sockfd, buf, BUFSIZE);
        if(n == 0)
            printf("the other side has been closed.\n");
        else/*打印输出服务端传过来的数据*/
            write(STDOUT_FILENO, buf, n);
    }

    close(sockfd);
    return 0;
}
