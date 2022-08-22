#include <lua.h>
#include <lauxlib.h>

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

void create(zhandle_t *zkhandle, char *str) {
    char path_buffer[64] = "abc";
    int bufferlen = sizeof(path_buffer);
    printf("create node in synchronous mode \n");
    int flag = zoo_create(zkhandle, str, "syn-node", 9, &ZOO_OPEN_ACL_UNSAFE, 0, path_buffer, bufferlen);
    if (flag != ZOK) {
        printf("create syn-node failed\n");
        exit(EXIT_FAILURE);
    } else { printf("created node is %s\n", path_buffer); }
}

void exists(zhandle_t *zkhandle, char *path) {
    int flag = zoo_exists(zkhandle, path, 1, NULL);
    if (flag) {
        printf("%s node already exist\n", path);
    } else {
        printf("%s node not exist\n", path);
    }
}

void getACL(zhandle_t *zkhandle, char *str) {
    struct ACL_vector acl;
    struct Stat stat;
    int flag = zoo_get_acl(zkhandle, str, &acl, &stat);
    if (flag == ZOK && acl.count > 0) {
        printf("-----------------the ACL of %s: ------------ \n", str);
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

static int call_lua_watch(int type, int state, const char *path);

void zookeeper_watcher_g(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx) {
    printf(">>> zookeeper_watcher_g \n");
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
    call_lua_watch(type, state, path);
}

static int _cb() {
    printf(">>> _cb \n");
    return 0;
}

static lua_State *ud = NULL;

static int call_lua_watch(int type, int state, const char *path) {
    printf(">>> call_lua_watch: type=%d state=%d path=%s \n", type, state, path);
    lua_State *L = ud;

    int top = lua_gettop(L);
    printf(">>> top=%d \n", top);
//    lua_pushvalue(L,1);
//    lua_rawgeti(L, LUA_REGISTRYINDEX, lua_watch);
//    lua_pushinteger(L, type);
//    lua_pushinteger(L, state);
//    lua_pushstring(L, path);
    lua_pcall(L, 0, 0, 0);
    printf(">>> call_lua_watch: over \n");
}

static int lregister_watch(lua_State *L) {
    printf(">>> register_watch \n");
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_settop(L, 1);                        //设置栈大小
//    lua_rawsetp(L, LUA_REGISTRYINDEX, _cb);
    lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_MAINTHREAD);
    ud = lua_tothread(L, -1);
    lua_pop(L, 1);
    return 0;
}

static int lzookeeper_init(lua_State *L) {
    size_t host_sz = 0;
    const char *host = luaL_checklstring(L, 1, &host_sz);
    int recv_timeout = luaL_checkinteger(L, 2);
    const clientid_t *clientid = lua_touserdata(L, 3);
    void *context = lua_touserdata(L, 4);
    int flags = luaL_checkinteger(L, 5);
    zhandle_t *zkhandle = zookeeper_init(host, zookeeper_watcher_g, recv_timeout, clientid, context, flags);
    if (zkhandle == NULL) {
        fprintf(stderr, "Error when connecting to zookeeper servers... \n");
        exit(EXIT_FAILURE);
    }
    create(zkhandle, "/abc");
    exists(zkhandle, "/abc");
    getACL(zkhandle, "/abc");
    delete(zkhandle, "/abc");

    //轻量级用户数据，返回c指针
    lua_pushlightuserdata(L, zkhandle);
    return 1;
}

int luaopen_zk_client(lua_State *L) {
    luaL_Reg l[] = {
            {"register_watch", lregister_watch},
            {"zookeeper_init", lzookeeper_init},
            {NULL, NULL},
    };
    luaL_newlib(L, l);
    return 1;
}