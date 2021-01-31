//latihan 8-1 - it will wait until the STDIN file descriptor is ready without any timeout instead of 2.5 seconds

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define STDIN 0  //fd for std in

int main(void) {
    // struct timeval tv;
    fd_set readfds;

    // tv.tv_sec = 0;
    // tv.tv_usec = 0;

    printf("tidak membuat apa-apa atau tekan sebarang kekunci kemudian <enter>\n\n");

    FD_ZERO(&readfds);
    FD_SET(STDIN, &readfds);

    //Hanya readfds
    select(STDIN + 1, &readfds, NULL, NULL, NULL);

    if (FD_ISSET(STDIN, &readfds))
        printf("satu kekunci telah ditekan!\n");

    else
        printf("Masa tamat\n");

    return 0;
}