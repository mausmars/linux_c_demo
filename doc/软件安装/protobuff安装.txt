wget https://pkg-config.freedesktop.org/releases/pkg-config-0.29.2.tar.gz
./configure --with-internal-glib
make
make check
make install
//----------------------------------------------------------------
https://github.com/protobuf-c/protobuf-c/tree/v1.3.2

git clone https://github.com/protobuf-c/protobuf-c.git
git checkout v1.3.2

git clone 下载源码
git tag　列出所有版本号
git checkout　+某版本号　
//----------------------------------------------------------------
linux下添加动态链接库路径的方法
https://www.cnblogs.com/ostin/p/9193029.html
//----------------------------------------------------------------
protoc-c --c_out=. student.proto
gcc student.pb-c.c protobuf_test.c -o main -lprotobuf-c
//----------------------------------------------------------------
