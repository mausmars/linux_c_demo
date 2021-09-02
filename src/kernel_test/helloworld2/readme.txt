https://www.cnblogs.com/sctb/p/13816110.html
https://blog.sourcerer.io/writing-a-simple-linux-kernel-module-d9dc3762c234

测试 kernel_test 目录下的 helloworld2

查看编号 244
创建设备文件，以便我们可以从用户空间与内核模块进行通信
mknod /dev/lkm_example c MAJOR 0
$ mknod /dev/lkm_example c 244 0
cat /dev/lkm_example

rm /dev/lkm_example
rmmod lkm_example

lsmod | grep lkm_example