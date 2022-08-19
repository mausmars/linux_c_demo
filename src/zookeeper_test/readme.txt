zookeeper 例子
https://cloud.tencent.com/developer/article/1142948

https://www.cnblogs.com/wataciii/p/4062780.html

使用多线程编译加 -DTHREADED  使用zookeeper_mt 库支持多线程

# 单线程编译
gcc -o zookeeper_s_test zookeeper_s_test.c -lzookeeper_st -I /usr/local/include/zookeeper/
执行：./zookeeper_s_test localhost:2181

# 多线程编译
cc -o zookeeper_m_test zookeeper_m_test.o  -I/usr/local/include/zookeeper/ -L/usr/local/lib/ -L/usr/local/lib/x86_64-linux-gnu/ -lzookeeper_mt
执行：./zookeeper_m_test localhost:2181