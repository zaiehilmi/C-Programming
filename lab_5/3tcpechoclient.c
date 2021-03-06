//Latihan 5-3 - use read() and write() instead of send() and recv().
//baris 47 & 54
#include "arpa/inet.h"

#define SAIZTIMBAL 1024

int main(int argc, char *argv[]) {
    int soketfd;
    char timbal[SAIZTIMBAL + 1];
    struct sockaddr_in alamLayan;

    //Mencipta sambungan soket TCP
    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soketfd < 0) {
        printf("Ralat untuk mencipta soket TCP");
        exit(1);
    }

    printf("\t ####################\n");
    printf("\t ##  tcpechoclient ##\n");
    printf("\t ####################\n");

    //cipta struktur alamat untuk pelayan menghantar data
    bzero((char *)&alamLayan, sizeof(alamLayan));

    //maklumat soket pelayan
    alamLayan.sin_family = AF_INET;
    alamLayan.sin_port = htons(TCP_SERVER_ECHO_PORT);
    inet_pton(AF_INET, argv[1], &alamLayan.sin_addr);

    //menghubungkan ke pelayan
    int temp = connect(soketfd, (struct sockaddr *)&alamLayan, sizeof(alamLayan));
    if (temp < 0) {
        printf("Tidak boleh disambungkan\n");
        exit(5);
    }

    printf("Telah disambungkan ke pelayan %s ...\n", inet_ntoa(alamLayan.sin_addr));

    do {
        printf("Masukkan mesej..\n");
        // gets(timbal);
        fgets(timbal, SAIZTIMBAL, stdin);

        //hantar mesej melalui soketfd
        // send(soketfd, timbal, SAIZTIMBAL, 0);
        write(soketfd, timbal, SAIZTIMBAL);

        //kosongkan mesej daripada pelayan
        bzero(timbal, sizeof(timbal));

        //menerima mesej daripada pelayan
        // recv(soketfd, timbal, SAIZTIMBAL, 0);
        read(soketfd, timbal, SAIZTIMBAL);
        printf("Menerima kembali: %s\n\n", timbal);

    } while (strcmp(timbal, "\bye"));

    return 0;
}