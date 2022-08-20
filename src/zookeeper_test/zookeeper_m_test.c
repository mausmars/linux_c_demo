#include<stdio.h>
#include<string.h>
#include <zookeeper/zookeeper.h>
#include <zookeeper/zookeeper_log.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <errno.h>

static const char *state2String(int state) {
    if (state == 0) return "CLOSED_STATE";
    if (state == ZOO_CONNECTING_STATE) return "CONNECTING_STATE";
    if (state == ZOO_ASSOCIATING_STATE) return "ASSOCIATING_STATE";
    if (state == ZOO_CONNECTED_STATE) return "CONNECTED_STATE";
    if (state == ZOO_EXPIRED_SESSION_STATE) return "EXPIRED_SESSION_STATE";
    if (state == ZOO_AUTH_FAILED_STATE) return "AUTH_FAILED_STATE";
    return "INVALID_STATE";
}

static const char *type2String(int state) {
    if (state == ZOO_CREATED_EVENT) return "CREATED_EVENT";
    if (state == ZOO_DELETED_EVENT) return "DELETED_EVENT";
    if (state == ZOO_CHANGED_EVENT) return "CHANGED_EVENT";
    if (state == ZOO_CHILD_EVENT) return "CHILD_EVENT";
    if (state == ZOO_SESSION_EVENT) return "SESSION_EVENT";
    if (state == ZOO_NOTWATCHING_EVENT) return "NOTWATCHING_EVENT";
    return "UNKNOWN_EVENT_TYPE";
}

void zookeeper_watcher_g(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx) {
    printf("\nSomething happened.\n");
    printf("type: %s\n", type2String(type));
    printf("state: %s\n", state2String(state));
    printf("path: %s\n", path);
    printf("watcherCtx: %s\n", (char *) watcherCtx);
    const clientid_t *zk_clientid;
    int rc;
    if (type == ZOO_CREATED_EVENT) {
        printf("[%s %d] znode %s created.\n", __FUNCTION__, __LINE__, path);
    } else if (type == ZOO_DELETED_EVENT) {
        printf("[%s %d] znode %s deleted.\n", __FUNCTION__, __LINE__, path);
    } else if (type == ZOO_CHANGED_EVENT) {
        printf("[%s %d] znode %s changed.\n", __FUNCTION__, __LINE__, path);
    } else if (type == ZOO_CHILD_EVENT) {
        printf("[%s %d] znode %s children changed.\n", __FUNCTION__, __LINE__, path);
    } else if (type == ZOO_SESSION_EVENT) {
        if (state == ZOO_EXPIRED_SESSION_STATE) {
            printf("[%s %d] zookeeper session expired\n", __FUNCTION__, __LINE__);
        } else if (state == ZOO_AUTH_FAILED_STATE) {
            printf("[%s %d] zookeeper session auth failed\n", __FUNCTION__, __LINE__);
        } else if (state == ZOO_CONNECTING_STATE) {
            printf("[%s %d] zookeeper session is connecting\n", __FUNCTION__, __LINE__);
        } else if (state == ZOO_ASSOCIATING_STATE) {
            printf("[%s %d] zookeeper session is associating state\n", __FUNCTION__, __LINE__);
        } else if (state == ZOO_CONNECTED_STATE) {
            zk_clientid = zoo_client_id(zh);
            printf("[%s %d] connected to zookeeper server with clientid=%lu\n", __FUNCTION__, __LINE__,
                   zk_clientid->client_id);
        } else if (state == ZOO_NOTWATCHING_EVENT) {
            printf("[%s %d] zookeeper session remove watch\n", __FUNCTION__, __LINE__);
        } else {
            printf("unknown session event state = %s, path = %s, ctxt=%s\n", state2String(state), path,
                   (char *) watcherCtx);
        }
    }
}

void create(zhandle_t *zkhandle, char *str) {
    char path_buffer[64] = "abc";
    int bufferlen = sizeof(path_buffer);
    printf("create node in synchronous mode-----------------------\n");
    int flag = zoo_create(zkhandle, str, "syn-node", 9, &ZOO_OPEN_ACL_UNSAFE, 0, path_buffer, bufferlen);
    if (flag != ZOK) {
        printf("create syn-node failed\n");
        exit(EXIT_FAILURE);
    } else { printf("created node is %s\n", path_buffer); }
}

void exists(zhandle_t *zkhandle, char *path) {
    int flag = zoo_exists(zkhandle, path, 1, NULL);
    if (flag) { printf("%s node already exist\n", path); } else { printf("%s node not exist\n", path); }
}

void getACL(zhandle_t *zkhandle, char *str) {
    struct ACL_vector acl;
    struct Stat stat;
    int flag = zoo_get_acl(zkhandle, str, &acl, &stat);
    if (flag == ZOK && acl.count > 0) {
        printf("-----------------the ACL of %s:\n------------", str);
        printf("%d\n", acl.count);
        printf("%d\n", acl.data->perms);
        printf("%s\n", acl.data->id.scheme);
        printf("%s\n", acl.data->id.id);
    }
}

void delete(zhandle_t *zkhandle, char *str) {
    int flag = zoo_delete(zkhandle, str, -1);
    if (flag == ZOK) { printf("delete node %s success\n", str); }
}

int main(int argc, const char *argv[]) {
    const char *host = "localhost:2181";
    int timeout = 30000;
    char buffer[512];
    int *bufferlen;
    zoo_set_debug_level(ZOO_LOG_LEVEL_DEBUG);
    zhandle_t *zkhandle = zookeeper_init(host, zookeeper_watcher_g, timeout, 0, NULL, 0);
    if (zkhandle == NULL) {
        fprintf(stderr, "Error when connecting to zookeeper servers...\n");
        exit(EXIT_FAILURE);
    }
    create(zkhandle, "/abc");
    exists(zkhandle, "/abc");
    getACL(zkhandle, "/abc");
    delete(zkhandle, "/abc");
    while (1);
    zookeeper_close(zkhandle);
}