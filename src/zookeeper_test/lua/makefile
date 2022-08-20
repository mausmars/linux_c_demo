CC ?= gcc
CFLAGS = -g -O2 -Wall -I$(LUA_INC) -I$(ZK_INC) -L$(ZK_LIB)
SHARED := -fPIC --shared

TARGET = zk_client.so
LUA_CLIB_PATH = clib

# 引入lua头文件 github 下载的lua5.3.6版本
LUA_INC = /mnt/e/work/git_src/lua
ZK_INC = /mnt/e/work/git_src/zookeeper/zookeeper-client/zookeeper-client-c/include
ZK_LIB = /mnt/e/work/git_src/zookeeper/zookeeper-client/zookeeper-client-c/.lib

start: $(TARGET)

$(TARGET) : zk_client.c | $(LUA_CLIB_PATH)
	$(CC) $(CFLAGS) $(SHARED) $^ -o $@ -lzookeeper_mt

clean:
	rm -fr $(TARGET)

$(LUA_CLIB_PATH) :
	mkdir $(LUA_CLIB_PATH)
