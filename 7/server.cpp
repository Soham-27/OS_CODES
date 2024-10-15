#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <unistd.h>

using namespace std;

int main() {
// ftok to generate unique key
key_t key = ftok("shmfile", 65);

// shmget returns an identifier for the shared memory
int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

// shmat to attach the shared memory
char *sharedMemory = (char*) shmat(shmid, (void*)0, 0);

// Write a message to the shared memory
string message = "Hello from Server!";
strcpy(sharedMemory, message.c_str());

cout << "Message written to shared memory: " << sharedMemory <<
endl;

// Detach from shared memory
shmdt(sharedMemory);

// Server keeps running to demonstrate shared memory persistence

cout << "Server is waiting... (Press Ctrl + C to terminate)" <<
endl;
while (true) {
sleep(1); // Keep the server running
}

return 0;
}
