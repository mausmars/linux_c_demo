#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256
#define DEVICE_NAME "/dev/babel"
static char buffer[BUFFER_LENGTH];

int main() {
    int ret, fd;
    //   Open the device.
    printf("Opening to %s...", DEVICE_NAME);
    fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device...");
        return errno;
    }
    printf("Connected!");

    printf("Reading from the device...\n");
    ret = read(fd, buffer, BUFFER_LENGTH);
    if (ret < 0) {
        perror("Failed to read the message from the device.");
        return errno;
    }
    printf("The received message is: [%s]\n", buffer);
    return 0;
}