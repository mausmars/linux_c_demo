malloc_conf 配置
prof:true       开启监控模块

jemalloc 调用 mallctl("prof.dump") 生成.heap文件
mallctl("prof.dump", NULL, NULL, NULL, 0);


查看内存细节
jeprof mem_leak_test2 jeprof.15894.0.m0.heap
(jeprof) top

-----------------------------------------------------------
apt update
apt -y install ghostscript
apt install graphviz

生成pdf
jeprof --show_bytes --pdf mem_leak_test1 jeprof.17853.2.m2.heap > show2.pdf
jeprof --show_bytes --pdf mem_leak_test1 jeprof.17853.3.m3.heap > show3.pdf

对比2个文件
jeprof --dot mem_leak_test1 -base=jeprof.17853.2.m2.heap jeprof.17853.3.m3.heap

------------------------------------------------------------------
使用过程中可能出现的问题：
1.运行时出现：No nodes to print
程序逻辑使用CPU次数太少，无法分析

2.程序core dump
循环次数过多（原因不确定）

3.运行进出现：SIGPROF handler is already in use
使用了其它的性能分析工具如：gprof等，造成冲突

------------------------------------------------------------------
测试3
gcc -DJEMALLOC_NO_DEMANGLE -static -o mem_leak_test3 mem_leak_test3.c -I/usr/local/jemalloc/include -L/usr/local/jemalloc/lib  -ljemalloc -lpthread -ldl -lm
./test_mem_leak3.sh

jeprof --show_bytes --pdf mem_leak_test3 test3.2102.0.m0.heap > show_test3_0.pdf
jeprof --show_bytes --pdf mem_leak_test3 test1.1983.1.m1.heap > show_test3_1.pdf

------------------------------------------------------------------






