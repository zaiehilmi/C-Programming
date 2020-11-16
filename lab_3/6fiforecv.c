#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SAIZTIMBAL 100

char *fifo = "penghantaranfifo";  //nama fail fifo

int main(int argc, char const *argv[]) {
    int fd;
    char timbal[SAIZTIMBAL];

    int binafail = mkfifo(fifo, 0766);  //bina fail fifo dgn kod akses 766
    if (binafail == -1 && errno != EEXIST) {
        perror("Ralat pada mkfifo()\n");
        exit(1);
    }

    fd = open(fifo, O_RDWR);
    if (fd < 0) {  //buka fail fifo untuk memulakan read and write
        perror("Ralat pada open()\n");
        exit(2);
    }

    for (;;) {
        if (read(fd, timbal, SAIZTIMBAL - 1) < 0)
            perror("Ralat pada read()\n");

        printf("Diterima: %s\n", timbal);
        // if (timbal == )
        //     exit(3);
    }
    return 0;
}
