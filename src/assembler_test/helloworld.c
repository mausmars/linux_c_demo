#include <unistd.h>

#define len 14
char msg[len] = "Hello, world!\n";

int main(void) {
	write(1, msg, len);
	_exit(0);
}
