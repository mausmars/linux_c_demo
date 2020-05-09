stdatomic.h 需要GCC 4.9.3 不然编译报错

CentOS7 安装GCC 4.9.3
$ wget http://ftp.gnu.org/gnu/gcc/gcc-4.9.3/gcc-4.9.3.tar.bz2

$ tar xfv gcc-4.9.3.tar.bz2
$ cd gcc-4.9.3
$ ./contrib/download_prerequisites

如果连接失败，无法下载的话，就打开此文件，手动下载下面5个文件，然后将文件放在gcc根目录，再屏蔽contrib/download_prerequisites文件里面的wget操作，再重新执行一次./contrib/download_prerequisites。这样的话，后面编译gcc时，这几个依赖库会自动先编译，不用自动手动一个个编译。
cloog-0.18.1.tar.gz
gmp-4.3.2.tar.bz2
isl-0.12.2.tar.bz2
mpc-0.8.1.tar.gz
mpfr-2.4.2.tar.bz2

创建GCC临时编译目录
$ cd ..
$ mkdir build-gcc
$ cd build-gcc
$ ../gcc-4.9.3/configure --enable-checking=release --enable-languages=c,c++ --disable-multilib
$ make -j8     // -j利用多核处理器加快速度，机器核数*2
$ make install

----------------
gcc 编译配置参数说明:
--enable-languages        //指定 gcc 能编译哪些语言的文件，每种语言用逗号分隔, 例如 c,c++,Java
--disable-multilib           //默认gcc 能在32位系统上将代码编译成64位程序，或者在64位系统上编译成32位程序，如果加上这个编译选项则表示关闭这个gcc的交叉编译功能。
----------------

在etc/profile配置库文件和头文件路径
$ vi /etc/profile
export LD_LIBRARY_PATH=/usr/local/lib:/usr/local/lib64/:$LD_LIBRARY_PATH
export C_INCLUDE_PATH=/usr/local/include/:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/usr/local/include/:$CPLUS_INCLUDE_PATH

$ source /etc/profile

$ gcc -v
