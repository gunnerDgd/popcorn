#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main()                                             {
    int  fd      = open("/dev/hello_world_dev", O_RDWR);
    char buf[64] = { 0x00, };

    ssize_t ret = read(fd, buf, 64);
    printf("Read %d Bytes (Buf : %s)\n", ret, buf);

    const char* msg = "Hello UserMode Device !!";
    ret = write(fd, msg, strlen(msg));
    printf("Wrote %d Bytes\n", ret);
}