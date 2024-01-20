#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

int main()                                        {
    char file_buf[512] = { 0,  }                  ;
    int  file          = open("/dev/Test", O_RDWR);

    read (file, file_buf, 512);
    write(file, file_buf, 512);
    close(file)               ;
}