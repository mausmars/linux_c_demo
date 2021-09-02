测试 kernel_test 目录下的 babel

$ mknod /dev/babel c 244 0
cat /dev/babel

chmod 755 babel_client_w
chmod 755 babel_client_r

insmod babel.ko
查看编号 244
dmesg
mknod /dev/lkm_example c 244 0

向设备文件写数据
./babel_client_w
从设备文件读取数据
./babel_client_r

rm /dev/babel
rmmod babel
lsmod | grep babel