zookeeper 例子
https://cloud.tencent.com/developer/article/1142948

https://www.cnblogs.com/wataciii/p/4062780.html

使用多线程编译加 -DTHREADED  使用zookeeper_mt 库支持多线程


cd /mnt/e/work/demo/linux_c_demo/src/zookeeper_test

# 单线程编译
gcc -o zookeeper_s_test zookeeper_s_test.c -I/mnt/e/work/git_src/zookeeper/zookeeper-client/zookeeper-client-c/include -lzookeeper_st
./zookeeper_s_test

# 多线程编译
gcc -o zookeeper_m_test zookeeper_m_test.c  -I/mnt/e/work/git_src/zookeeper/zookeeper-client/zookeeper-client-c/include -L/usr/local/lib/ -L/usr/local/lib/x86_64-linux-gnu/ -L/mnt/e/work/git_src/zookeeper/zookeeper-client/zookeeper-client-c -lzookeeper_mt

./zookeeper_m_test





