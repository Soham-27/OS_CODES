// p1.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd_write, fd_read;
    char *myfifo1 = "/tmp/myfifo1"; // For writing
    char *myfifo2 = "/tmp/myfifo2"; // For reading

    // Create two FIFOs for full-duplex communication
    mkfifo(myfifo1, 0666);	
    mkfifo(myfifo2, 0666);

    char arr1[180], arr2[180];

    while (1) {
        // Write to p2
        fd_write = open(myfifo1, O_WRONLY);
        printf("\nEnter a sentence: ");
        fgets(arr2, 180, stdin);
        write(fd_write, arr2, strlen(arr2) + 1);
        close(fd_write);

        // Read from p2
        fd_read = open(myfifo2, O_RDONLY);
        read(fd_read, arr1, sizeof(arr1));
        printf("Received from User2:\n %s\n", arr1);
        close(fd_read);
    }
    exit(EXIT_SUCCESS);
}


