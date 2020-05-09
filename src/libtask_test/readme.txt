安装 libtask

https://github.com/jamwt/libtask

下载 libtask.tar.gz
解压
tar -zxvf libtask.tar.gz 
cd libtask
make
生成 libtask.a 静态库

=====================================

export LD_LIBRARY_PATH=/data/soft/libtask/:$LD_LIBRARY_PATH 
export C_INCLUDE_PATH=/data/soft/libtask/:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/data/soft/libtask/:$CPLUS_INCLUDE_PATH

//依赖静态库
$ gcc libtask_test1.c -o libtask_test1 /data/soft/libtask/libtask.a






