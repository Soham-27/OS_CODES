#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

using namespace std;

int main() {
char inputStr[100];
int fd1, fd2;

// Create FIFOs (named pipes)
mkfifo(FIFO1, 0666); // Create FIFO1 for sending data to
Process 2
mkfifo(FIFO2, 0666); // Create FIFO2 for receiving response
from Process 2

while (true) {
// Writing to FIFO1
cout << "Enter a sentence (type 'exit' to quit): ";
cin.getline(inputStr, 100);

if (strcmp(inputStr, "exit") == 0) {
break;
}

// Send sentence to Process 2
fd1 = open(FIFO1, O_WRONLY);
write(fd1, inputStr, strlen(inputStr) + 1);
close(fd1);

// Reading from FIFO2 (response from Process 2)
char outputStr[100];
fd2 = open(FIFO2, O_RDONLY);
read(fd2, outputStr, sizeof(outputStr));
close(fd2);

// Display the result received from Process 2
cout << "Process 2 response: " << outputStr << endl;
}

// Clean up the FIFOs
unlink(FIFO1);
unlink(FIFO2);

return 0;
}
