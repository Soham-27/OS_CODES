#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
pthread_mutex_t wr, mutex;
int a = 10, readcount = 0;
void *reader(void *arg) {
long int num = (long int)arg;
while (1) {
pthread_mutex_lock(&mutex);
readcount++;
if (readcount == 1) {
pthread_mutex_lock(&wr);
}
pthread_mutex_unlock(&mutex);
printf("\nReader %ld is in critical section", num);
printf("\nReader %ld reading data %d", num, a);
sleep(1);
pthread_mutex_lock(&mutex);
readcount--;
if (readcount == 0) {
pthread_mutex_unlock(&wr);
}
pthread_mutex_unlock(&mutex);
printf("\nReader %ld has left critical section", num);
sleep(rand() % 10);
}
return NULL;
}
void *writer(void *arg) {
long int num = (long int)arg;
while (1) {
pthread_mutex_lock(&wr);
printf("\nWriter %ld is in critical section", num);
a++;
printf("\nWriter %ld has written data as %d", num, a);
sleep(1);
pthread_mutex_unlock(&wr);
printf("\nWriter %ld has left critical section", num);
sleep(rand() % 10);
}
return NULL;
}
int main() {

pthread_t r[10], w[10];
long int i, j;
int nor, now;
pthread_mutex_init(&wr, NULL);
pthread_mutex_init(&mutex, NULL);
printf("Enter the number of readers:\n");
scanf("%d", &nor);
printf("Enter the number of writers:\n");
scanf("%d", &now);
for (i = 0; i < nor; i++) {
pthread_create(&r[i], NULL, reader, (void *)i);
}
for (j = 0; j < now; j++) {
pthread_create(&w[j], NULL, writer, (void *)j);
}
for (i = 0; i < nor; i++) {
pthread_join(r[i], NULL);
}
for (j = 0; j < now; j++) {
pthread_join(w[j], NULL);
}
pthread_mutex_destroy(&wr);
pthread_mutex_destroy(&mutex);
return 0;
}
