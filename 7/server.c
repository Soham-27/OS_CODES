#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main() {
// Generate a unique key for the shared memory segment
key_t key = ftok("shmfile", 65);
// Create a shared memory segment with the size of 1024 bytes
int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
// Attach to the shared memory
char *str = (char *) shmat(shmid, (void *)0, 0);
printf("Enter a message to write to shared memory: ");
fgets(str, 1024, stdin);
// Detach from shared memory
shmdt(str);
return 0;
}
