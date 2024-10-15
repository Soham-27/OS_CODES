#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define N 10
int buffer[N];
int in = 0, out = 0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
void print_buffer() {
printf("Buffer: [ ");
for (int i = 0; i < N; i++) {
printf("%d ", buffer[i]);
}
printf("]\n");
}
void* producer(void* arg) {
int id = *(int*)arg;
while (1) {
int k = rand() % 10;
sem_wait(&empty);
pthread_mutex_lock(&mutex);
buffer[in] = k;
printf("Producer %d inserted item: %d\n", id, k);
print_buffer();
in = (in + 1) % N;
pthread_mutex_unlock(&mutex);
sem_post(&full);
sleep(rand() % 7);
}
return NULL;
}
void* consumer(void* arg) {
int id = *(int*)arg;
while (1) {
sem_wait(&full);
pthread_mutex_lock(&mutex);
int k = buffer[out];
printf("Consumer %d consumed item: %d\n", id, k);
buffer[out] = 0; // Mark the consumed item as 0 to indicate it's

print_buffer();
out = (out + 1) % N;
pthread_mutex_unlock(&mutex);
sem_post(&empty);
sleep(rand() % 7);
}
return NULL;

}

int main() {
int p, q;
printf("Enter number of producers: ");
scanf("%d", &p);
printf("Enter number of consumers: ");
scanf("%d", &q);
pthread_t producers[p];
pthread_t consumers[q];
sem_init(&empty, 0, N);
sem_init(&full, 0, 0);
pthread_mutex_init(&mutex, NULL);
int producer_ids[p];
int consumer_ids[q];
for (int i = 0; i < p; i++) {
producer_ids[i] = i;
pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
}
for (int i = 0; i < q; i++) {
consumer_ids[i] = i;
pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
}
for (int i = 0; i < p; i++) {
pthread_join(producers[i], NULL);
}
for (int i = 0; i < q; i++) {
pthread_join(consumers[i], NULL);
}
sem_destroy(&full);
sem_destroy(&empty);
pthread_mutex_destroy(&mutex);
return 0;
}
