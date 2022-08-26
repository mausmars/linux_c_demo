https://www.cnblogs.com/jiqingwu/p/linux_dynamic_lib_create.html

----------------------------------------------------------
可以使用
export LD_LIBRARY_PATH=

LD_LIBRARY_PATH 

-rpath-link：这个也是用于“链接”的时候的，例如你显示指定的需要 FOO.so，但是 FOO.so 本身是需要 BAR.so 的，后者你并没有指定，而是 FOO.so 引用到它，这个时候，
会先从 -rpath-link 给的路径里找。

-rpath: “运行”的时候，去找的目录。运行的时候，要找 .so 文件，会从这个选项里指定的地方去找。对于交叉编译，交叉编译链接器需已经配置 –with-sysroot 选项才能起作用。
也就是说，-rpath指定的路径会被记录在生成的可执行程序中，用于运行时查找需要加载的动态库。

-Wa,<options>            Pass comma-separated <options> on to the assembler
-Wp,<options>            Pass comma-separated <options> on to the preprocessor
-Wl,<options>            Pass comma-separated <options> on to the linker

rpath和-rpath-link都可以在链接时指定库的路径；但是运行可执行文件时，
-rpath-link指定的路径就不再有效(链接器没有将库的路径包含进可执行文件中)
-rpath指定的路径还有效(因为链接器已经将库的路径包含在可执行文件中了。)
不管使用了-rpath还是-rpath-link，LD_LIBRARY_PATH还是有效的。
----------------------------------------------------------
生成maxtest.so  动态库
gcc -fPIC -shared -o libmaxtest.so max_test.c

生成mathtest.so  动态库
gcc -fPIC -shared -L../max -I../max -o libmathtest.so math_test.c -lmaxtest -Wl,--rpath=/mnt/e/work/demo/linux_c_demo/src/dll_test/max

编译test 生成执行文件
gcc -Lmath -Imath test.c -lmathtest -Wl,--rpath=math

---------------------------------------
相对路径有问题
gcc -fPIC -shared -L../max -I../max -o libmathtest.so math_test.c -lmaxtest -Wl,--rpath=../max

注意：rpath使用相对路径的问题，在不同路径下查看信息不一样。

在dll_test路径下查看 ldd math/libmathtest.so
        linux-vdso.so.1 (0x00007fffc52a2000)
        libmaxtest.so => not found              未找到。。。
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f1f91860000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f1f92000000)

在math路径下查看 ldd math/libmathtest.so
        linux-vdso.so.1 (0x00007fffce6d7000)
        libmaxtest.so => ../max/libmaxtest.so (0x00007f0daeb40000)      正常的
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f0dae740000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f0daf000000)
---------------------------------------