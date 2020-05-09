#include "net_server_epoll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nolock_queue.h"

void testcQueue() {
    Queue *queue = createQueue();

    int value = 10;

    addQueue(queue, &value);

    int *data = (int *) pollQueue(queue);
    printf("data=%d", *data);
}

void testNetServer() {
    NetServer *server = NULL;

    char explain[255];
    strcpy(explain, "----------------------------\n");
    strcat(explain, "输入指令序号\n");
    strcat(explain, "0.退出测试\n");
    strcat(explain, "1.启动tcp服务\n");
    strcat(explain, "2.关闭tcp服务");

    int i;
    bool isOver = false;
    for (;;) {
        puts(explain);
        scanf("%d", &i);
        switch (i) {
            case 0:
                isOver = true;
                if (server != NULL) {
                    shutdownNetServer(server);
                }
                break;
            case 1:
                server = createNetServer(NULL);
                startupNetServer(server);
                break;
            default:
                break;
        }
        if (isOver) {
            break;
        }
    }
}

int main(int argc, const char *argv[]) {
    testNetServer();
//    testcQueue();
    return 0;
}