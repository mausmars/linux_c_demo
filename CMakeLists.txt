#1.cmake verson，指定cmake版本
cmake_minimum_required(VERSION 3.16)

#2.project name，指定项目的名称，一般和项目的文件夹名称对应
project(linuxc_demo C)

#3.head file path，头文件目录
INCLUDE_DIRECTORIES(
        include
        /usr/include
        /usr/local/include

        /usr/local/jemalloc/include
        /usr/include/mysql
        /software/php-src
        /software/php-src/Zend

        /usr/local/include/luajit-2.1
)
#/mnt/e/work/git_src/lua

#设置编译器（可选的有gcc，g++）
set(CMAKE_CXX_COMPILER "gcc")

# 设置用debug还是release模式。debug允许断点，而release更快
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

# 设置编译选项
set(CMAKE_C_STANDARD 11)

find_package(Threads)
#add_executable(demo_linuxc1 src/sync_test/sync_test1.c)
#add_executable(demo_linuxc1 src/sync_test/account.c src/sync_test/accouotn_test.c src/sync_test/common.h src/sync_test/cal_test.c)
#add_executable(demo_linuxc1 src/sync_test/sync_test3.c src/sync_test/model.h)
add_executable(rbtree_test src/algorithm_test/rbtree_test.c src/algorithm_test/rbtree.c)
add_executable(rbtree_test2 src/algorithm_test/rbtree_test2.c src/algorithm_test/rbtree.c)
add_executable(threadlocal_test src/thread_test/thread_local_test.c)
add_executable(sync_test src/sync_test/sync_test2.c src/sync_test/model.h)
add_executable(jemalloc_demo src/malloc_test/jemalloc_test.c)
add_executable(malloc_demo src/malloc_test/malloc_test.c)
add_executable(mysql_test src/mysql_test/mysql_test.c)
#add_executable(demo_linuxc1 src/protobuf_test/protobuf_test.c src/protobuf_test/student.pb-c.c)
add_executable(epoll_server src/epoll_test/server.c)
add_executable(epoll_client src/epoll_test/client.c)
add_executable(epoll_client3 src/epoll_test/client3.c)
add_executable(epoll_test_signal src/epoll_test/epoll_test_signal.c)
add_executable(epoll_test_pipe src/epoll_test/epoll_test_pipe.c)
add_executable(epoll_test_event src/epoll_test/epoll_test_event.c)
add_executable(attack_arp src/attack_test/SendAttackArp.c)
add_executable(attack_sync src/attack_test/SendAttackSync.c)
add_executable(attack_sync2 src/attack_test/SendAttackSync2.c)
add_executable(attack_icmp src/attack_test/SendAttackIcmp.c)
add_executable(sniffer src/attack_test/SimpelSniffer2.c)
add_executable(semaphore src/thread_test/thread_semaphore_test.c)
add_executable(httpserver src/httpserver_test/starter.c src/httpserver_test/httpd.h src/httpserver_test/httpd.c)
add_executable(networkcard1 src/networkcard_test/test1/networkcard_test1.c)
add_executable(networkcard2 src/networkcard_test/test2/networkcard_test2.c)
add_executable(coroutine_test src/coroutine/main.c src/coroutine/coroutine.c)
#基础api测试
add_executable(base_ucontext_test src/base_test/ucontext_test.c)
add_executable(base_pthread_self_test src/base_test/pthread_self_test.c src/base_test/itimerval_test.c)

file(GLOB attack_src src/common/*.h src/common/*.c src/attack/*.h src/attack/*.c)
add_executable(arp_attack ${attack_src})

file(GLOB game_server_src src/common/*.h src/common/*.c src/game_server/*.h src/game_server/*.c)
add_executable(gameserver ${game_server_src})

add_executable(atomic_test1 src/atomic_test/atomic_test1.c)
add_executable(atomic_test2 src/atomic_test/atomic_test2.c)

add_executable(udp_server src/net_test/udp_server.c)
add_executable(udp_client src/net_test/udp_client.c)

add_executable(porint_test src/base_test/point_test.c)

add_executable(luac_test1 src/luac_test/luac_test1.c)

add_executable(jmp_test src/jmp_test/jmp_test.c)

add_executable(libdatrie_test_file src/libdatrie_test/test_file.c src/libdatrie_test/utils.h src/libdatrie_test/utils.c)

#ADD_DEFINITIONS(
#        -DUSE_JEMALLOC
#)

target_link_libraries(rbtree_test)
target_link_libraries(rbtree_test2)
target_link_libraries(threadlocal_test ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(demo_linuxc1 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(mysql_test /usr/lib64/mysql/libmysqlclient.so.18)
#target_link_libraries(demo_linuxc1 /usr/local/lib/libprotobuf-c.so)
target_link_libraries(sync_test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(malloc_demo)
target_link_libraries(jemalloc_demo /usr/local/jemalloc/lib/libjemalloc.so)
target_link_libraries(epoll_server ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(epoll_client ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(epoll_client3 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(epoll_test_signal ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(epoll_test_pipe ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(epoll_test_event ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(attack_arp)
target_link_libraries(attack_sync)
target_link_libraries(attack_sync2)
target_link_libraries(attack_icmp)
target_link_libraries(sniffer)
target_link_libraries(semaphore ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(httpserver)
target_link_libraries(networkcard1)
target_link_libraries(networkcard2)
target_link_libraries(coroutine_test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(base_ucontext_test)
target_link_libraries(base_pthread_self_test ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(arp_attack ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gameserver ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(atomic_test1 ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(atomic_test2 ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(udp_server)
target_link_libraries(udp_client)

target_link_libraries(porint_test)

target_link_libraries(luac_test1 /usr/local/lib/libluajit-5.1.so)
#target_link_libraries(luac_test1)

target_link_libraries(jmp_test)

target_link_libraries(libdatrie_test_file /mnt/e/work/git_src/libdatrie/datrie/.libs/libdatrie.so)
