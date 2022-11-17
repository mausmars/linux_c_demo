# 编译被调试程序
gcc -O0 hello.c -o hello

# 编译调试器 demo
gcc main.c -o ptrace-example-linux

./ptrace-example-linux hello


----------------------------------------
apt -y install lldb
gcc -O0 -gdwarf-4 foo.c -o foo
生成 foo.dSYM 的目录

lldb foo
(lldb) target create "foo"
(lldb) b foo
(lldb) run






