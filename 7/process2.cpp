#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

using namespace std;

int countWords(const string& str) {
int wordCount = 0;
bool inWord = false;
for (char c : str) {
if (isspace(c)) {
inWord = false;
} else if (!inWord) {
inWord = true;
wordCount++;
}
}
return wordCount;
}

int main() {
char buffer[100];
int fd1, fd2;

// Create FIFOs (named pipes)
mkfifo(FIFO1, 0666); // Create FIFO1 for receiving data from
Process 1
mkfifo(FIFO2, 0666); // Create FIFO2 for sending response to
Process 1

while (true) {
// Reading from FIFO1
fd1 = open(FIFO1, O_RDONLY);
read(fd1, buffer, sizeof(buffer));
close(fd1);

string inputStr(buffer);

if (inputStr == "exit") {
break;
}

// Count characters, words, and lines
int charCount = inputStr.length();
int wordCount = countWords(inputStr);
int lineCount = count(inputStr.begin(), inputStr.end(),
'\n') + 1; // Only one line per sentence

// Write results to a text file
ofstream outFile("output.txt");
outFile << "Characters: " << charCount << endl;
outFile << "Words: " << wordCount << endl;
outFile << "Lines: " << lineCount << endl;
outFile.close();

// Send the contents of the text file to Process 1
ifstream inFile("output.txt");

string result((istreambuf_iterator<char>(inFile)),
istreambuf_iterator<char>());
inFile.close();

fd2 = open(FIFO2, O_WRONLY);
write(fd2, result.c_str(), result.length() + 1);
close(fd2);
}

// Clean up the FIFOs
unlink(FIFO1);
unlink(FIFO2);

return 0;
}
