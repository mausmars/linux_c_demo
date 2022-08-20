#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zookeeper/zookeeper.h>
#include <zookeeper/zookeeper_log.h>
#include <errno.h>

#define TRUE 1

static const char *state2String(int state) {
    if (state == 0)
        return "CLOSED_STATE";
    if (state == ZOO_CONNECTING_STATE)
        return "CONNECTING_STATE";
    if (state == ZOO_ASSOCIATING_STATE)
        return "ASSOCIATING_STATE";
    if (state == ZOO_CONNECTED_STATE)
        return "CONNECTED_STATE";
    if (state == ZOO_EXPIRED_SESSION_STATE)
        return "EXPIRED_SESSION_STATE";
    if (state == ZOO_AUTH_FAILED_STATE)
        return "AUTH_FAILED_STATE";

    return "INVALID_STATE";
}

static const char *type2String(int state) {
    if (state == ZOO_CREATED_EVENT)
        return "CREATED_EVENT";
    if (state == ZOO_DELETED_EVENT)
        return "DELETED_EVENT";
    if (state == ZOO_CHANGED_EVENT)
        return "CHANGED_EVENT";
    if (state == ZOO_CHILD_EVENT)
        return "CHILD_EVENT";
    if (state == ZOO_SESSION_EVENT)
        return "SESSION_EVENT";
    if (state == ZOO_NOTWATCHING_EVENT)
        return "NOTWATCHING_EVENT";

    return "UNKNOWN_EVENT_TYPE";
}

void zktest_dump_stat(const struct Stat *stat) {
    char tctimes[40];
    char tmtimes[40];
    time_t tctime;
    time_t tmtime;

    if (!stat) {
        fprintf(stderr, "null\n");
        return;
    }
    tctime = stat->ctime / 1000;
    tmtime = stat->mtime / 1000;

    ctime_r(&tmtime, tmtimes);
    ctime_r(&tctime, tctimes);

    fprintf(stderr, "\tctime = %s\tczxid=%llx\n"
                    "\tmtime=%s\tmzxid=%llx\n"
                    "\tversion=%x\taversion=%x\n"
                    "\tephemeralOwner = %llx\n",
            tctimes, stat->czxid,
            tmtimes, stat->mzxid,
            (unsigned int) stat->version, (unsigned int) stat->aversion,
            stat->ephemeralOwner);
}

void zktest_data_completion(int rc, const char *value, int value_len, const struct Stat *stat, const void *data) {
    fprintf(stderr, "in data completion [%s]: rc = %d\n", value, rc);
    zktest_dump_stat(stat);
}

/*process a list of string and stat*/
void
zktest_strings_stat_completion(int rc, const struct String_vector *strings, const struct Stat *stat, const void *data) {
    int i = 0;
    fprintf(stderr, "in strings state completion [%s]: rc = %d, string count %d\n", (char *) data, rc, strings->count);
    for (i = 0; i < strings->count; i++) {
        printf("%d: %s\n", i, strings->data[i]);
    }
    deallocate_String_vector(strings);
    zktest_dump_stat(stat);
}

void zktest_string_completion(int rc, const char *name, const void *data) {
    fprintf(stderr, "in string completion [%s]: rc = %d\n", (char *) (data == 0 ? "null" : data), rc);
    if (!rc) {
        fprintf(stderr, "\tname = %s\n", name);
    }
}

void zktest_stat_completion(int rc, const struct Stat *stat, const void *data) {

    if (rc == ZNONODE) {
        printf("node not exists\n");
    }
    fprintf(stderr, "in state completion rc = %d data=%s stat:\n", rc, (char *) data);
    zktest_dump_stat(stat);

}

void zktest_void_completion(int rc, const void *data) {
    fprintf(stderr, "in void completion [%s]: rc = %d\n", (char *) (data == 0 ? "null" : data), rc);
}


void zktest_watcher_g(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx) {
    printf("Something happened.\n");
    printf("type: %s\n", type2String(type));
    printf("state: %s\n", state2String(state));
    printf("path: %s\n", path);
    printf("watcherCtx: %s\n", (char *) watcherCtx);
    int ret;
    const clientid_t *zk_clientid;
    if (path == NULL || strlen(path) == 0) {
        path = "/xyz";
    }
    if (type == ZOO_SESSION_EVENT) {
        if (state == ZOO_EXPIRED_SESSION_STATE) {
            printf("[%s %d]zookeeper session expired\n", __FUNCTION__, __LINE__);
        } else if (state == ZOO_CONNECTED_STATE) {
            zk_clientid = zoo_client_id(zh);
            printf("[%s %d] connected to zookeeper server with clientid=%lu\n", __FUNCTION__, __LINE__,
                   zk_clientid->client_id);
            if ((ret = zoo_aexists(zh, path, TRUE, zktest_stat_completion, path)) != ZOK) {
                printf("[%s %d] zoo_aexists judge error, msg = %s\n", __FUNCTION__, __LINE__, zerror(ret));

            }
            if ((ret = zoo_aget(zh, (char *) path, TRUE, zktest_data_completion, "get param")) != ZOK) {
                printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret,
                       zerror(ret));
            }
            if ((ret = zoo_aget_children2(zh, path, TRUE, zktest_strings_stat_completion, "get children param")) !=
                ZOK) {
                printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret,
                       zerror(ret));
            }
        }
    } else if (type == ZOO_CREATED_EVENT) {
        printf("create a child node\n");

        if ((ret = zoo_aget_children2(zh, path, TRUE, zktest_strings_stat_completion, "get children param")) != ZOK) {
            printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret, zerror(ret));
        }
        if ((ret = zoo_aget(zh, path, TRUE, zktest_data_completion, "get param")) != ZOK) {
            printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret, zerror(ret));
        }

    } else if (type == ZOO_DELETED_EVENT) {
        printf("path %s deleted\n", path);
        if ((ret = zoo_aget(zh, path, TRUE, zktest_data_completion, "get param")) != ZOK) {
            printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret, zerror(ret));
        }
    } else if (type == ZOO_CHANGED_EVENT) {
        printf("path %s changed\n", path);
        if ((ret = zoo_aget_children2(zh, path, TRUE, zktest_strings_stat_completion, "get children param")) != ZOK) {
            printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret, zerror(ret));
        }
        if ((ret = zoo_aget(zh, path, TRUE, zktest_data_completion, "get param")) != ZOK) {
            printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret, zerror(ret));
        }

    } else if (type == ZOO_CHILD_EVENT) {
        printf("path %s child event\n");
        if ((ret = zoo_aget(zh, path, TRUE, zktest_data_completion, "get param")) != ZOK) {
            printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret, zerror(ret));
        }
        if ((ret = zoo_aget_children2(zh, path, TRUE, zktest_strings_stat_completion, "get children param")) != ZOK) {
            printf("[%s %d] fail to get znode %s, err=%d, msg= %s\n", __FUNCTION__, __LINE__, path, ret, zerror(ret));
        }
    } else if (type == ZOO_NOTWATCHING_EVENT) {
    } else {
        printf("unkown zoo event type\n");
    }
}


int main(int argc, const char *argv[]) {
    static const char *host = "localhost:2181";
    int timeout = 30000;
    zhandle_t *zkhandle;
    zoo_set_debug_level(ZOO_LOG_LEVEL_DEBUG);
    zoo_deterministic_conn_order(1);
    zkhandle = zookeeper_init(host, zktest_watcher_g, 30000, 0, "hello world", 0);
    if (zkhandle == NULL) {
        fprintf(stderr, "Error when connecting to zookeeper servers...\n");
        exit(EXIT_FAILURE);
    }

    /* Wait for asynchronous zookeeper call done.*/
    int fd, interest, events;
    int rc;
    fd_set rfds, wfds, efds;
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_ZERO(&efds);
    while (1) {
        struct timeval tv;
        zookeeper_interest(zkhandle, &fd, &interest, &tv);
        if (fd != -1) {
            if (interest & ZOOKEEPER_READ) {
                FD_SET(fd, &rfds);
            } else {
                FD_CLR(fd, &rfds);
            }

            if (interest & ZOOKEEPER_WRITE) {
                FD_SET(fd, &wfds);
            } else {
                FD_CLR(fd, &wfds);
            }
        } else {
            fd = 0;
        }

        if (select(fd + 1, &rfds, &wfds, &efds, &tv) < 0) {
            printf("[%s %d]select failed, err=%d, msg=%s\n", __FUNCTION__, __LINE__, errno, strerror(errno));
        }
        events = 0;
        if (FD_ISSET(fd, &rfds)) {
            events |= ZOOKEEPER_READ;
        }
        if (FD_ISSET(fd, &wfds)) {
            events |= ZOOKEEPER_WRITE;
        }
        zookeeper_process(zkhandle, events);
    }
    zookeeper_close(zkhandle);
}