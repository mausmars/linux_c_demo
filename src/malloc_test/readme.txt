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

