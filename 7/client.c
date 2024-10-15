#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
int main() {
// Generate a unique key to access the shared memory
key_t key = ftok("shmfile", 65);
// Locate the shared memory segment created by the server
int shmid = shmget(key, 1024, 0666);
// Attach to the shared memory
char *str = (char *) shmat(shmid, (void *)0, 0);
printf("Message read from shared memory: %s\n", str);

// Detach from shared memory
shmdt(str);
return 0;
}
