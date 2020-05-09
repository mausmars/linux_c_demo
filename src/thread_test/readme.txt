http://docs.linuxtone.org/ebooks/C&CPP/c/ch35s03.html

用挂起等待的方式解决访问冲突不见得是最好的办法，因为这样毕竟会影响系统的并发性，
在某些情况下解决访问冲突的问题可以尽量避免挂起某个线程，
例如Linux内核的Seqlock、RCU（read-copy-update）等机制


避免线程挂起的其他方式
1.原子库stdatomic.h
2.内核Seqlock
3.协程libtask
4.RCU（read-copy-update）


协程模型
lua的resume-yield
erlang的spawn