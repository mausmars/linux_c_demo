#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

/**
 * #include <sys/mman.h>
 * void *mmap(void *addr, size_t len, int prot, int flag, int filedes, off_t off);
 * int munmap(void *addr, size_t len);
 */
int main(void) {
	int *p;
	int fd = open("hello.txt", O_RDWR);
	if (fd < 0) {
		perror("open hello");
		exit(1);
	}
	p = mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	close(fd);
	p[0] = 0x30313233;
	munmap(p, 6);
	return 0;
}
