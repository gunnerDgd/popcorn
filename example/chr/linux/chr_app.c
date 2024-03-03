#include <nolibc.h>

int main(void)                                    {
    int  fd      = open("/dev/hello_world_dev", 2);
    char buf[64] = { 0x00, };

    ssize_t ret = read(fd, buf, 64);
    printf("[popcorn][chr-app] Read %d Bytes.\n", ret);
    printf("[popcorn][chr-app] Read %s.\n"      , buf);

    const char* msg = "Hello UserMode Device !!";
    ret = write(fd, msg, 24);
    printf("[popcorn][chr-app] Wrote %d Bytes.\n", ret);
}