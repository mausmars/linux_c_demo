----------------------------------------
as hello.s -o hello.o
ld hello.o -o hello
./hello

----------------------------------------
as -o helloworld.o helloworld.s
ld -o helloworld helloworld.o
./helloworld