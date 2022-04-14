as --64 -gstabs -o setjmp.o setjmp.s
gcc -ggdb -c -o jmpcall.o jmpcall.c
gcc -ggdb -o jmpcall setjmp.o jmpcall.o

./jmpcall