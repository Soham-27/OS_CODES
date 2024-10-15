#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd_read, fd_write;
    char *myfifo1 = "/tmp/myfifo1"; // For reading
    char *myfifo2 = "/tmp/myfifo2"; // For writing

    // Create the two FIFOs for full-duplex communication
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo2, 0666);

    char str1[180], str2[180];
    FILE *file;

    while (1) {
        // Read from p1
        fd_read = open(myfifo1, O_RDONLY);
        read(fd_read, str1, sizeof(str1));
        close(fd_read);

        // Print the read string
        printf("User1: %s\n", str1);

        // Count lines, words, and characters
        int lines = 0, words = 0, characters = 0;
        int i = 0;
        while (str1[i] != '\0') {
            characters++;
            if (str1[i] == ' ') words++;
            if (str1[i] == '.') lines++;
            i++;
        }
        words++; // Count last word

        // Prepare the result string
        snprintf(str2, sizeof(str2), "Words Count: %d\n Lines Count: %d\n Characters Count: %d", words, lines, characters-1);

        // Write results to a file
        file = fopen("results.txt", "a");
        fprintf(file, "%s\n", str2);
        fclose(file);

        // Send back the results to p1
        fd_write = open(myfifo2, O_WRONLY);
        write(fd_write, str2, strlen(str2) + 1);
        close(fd_write);
    }

    // Clean up
    //unlink(myfifo1);
    //unlink(myfifo2);
    return 0;
}	
