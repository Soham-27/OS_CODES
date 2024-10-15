#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <unistd.h>

#define MAX_BUFFER_SIZE 10 // Maximum size of the buffer
#define TOTAL_ITEMS 20 // Total items to produce and consume

std::queue<int> buffer; // Shared buffer
int produced_count = 0; // Count of produced items
int consumed_count = 0; // Count of consumed items

pthread_mutex_t mutex; // Mutex for buffer access
sem_t empty_slots; // Semaphore to count empty slots in the
buffer
sem_t filled_slots; // Semaphore to count filled slots in the
buffer

// Producer function
void* producer(void* param) {
long producer_id = (long)param;

while (produced_count < TOTAL_ITEMS) { // Total items to produce
// Produce an item
sleep(1); // Simulate time taken to produce
int item = produced_count + 1; // Create item
produced_count++;

// Wait for an empty slot in the buffer
sem_wait(&empty_slots);

pthread_mutex_lock(&mutex); // Lock for buffer access

// Add item to the buffer
buffer.push(item);
std::cout << "Producer " << producer_id << " produced item:
" << item << std::endl;

pthread_mutex_unlock(&mutex); // Unlock buffer
sem_post(&filled_slots); // Signal that a new item has
been produced
}

return NULL;
}

// Consumer function
void* consumer(void* param) {
long consumer_id = (long)param;

while (consumed_count < TOTAL_ITEMS) { // Total items to consume
// Wait for a filled slot in the buffer
sem_wait(&filled_slots);
pthread_mutex_lock(&mutex); // Lock for buffer access

// Check if buffer is empty (this is just a precaution)
if (!buffer.empty()) {
// Remove item from the buffer
int item = buffer.front();
buffer.pop();
consumed_count++;
std::cout << "Consumer " << consumer_id << " consumed
item: " << item << std::endl;
}

pthread_mutex_unlock(&mutex); // Unlock buffer
sem_post(&empty_slots); // Signal that an empty slot
has been freed

// To demonstrate waiting:
if (buffer.empty()) {
std::cout << "Consumer " << consumer_id << " is waiting
for items..." << std::endl;
}

sleep(1); // Simulate time taken to consume
}

return NULL;
}

int main() {
int num_producers, num_consumers;

std::cout << "Enter the number of producers: ";
std::cin >> num_producers;
std::cout << "Enter the number of consumers: ";
std::cin >> num_consumers;

pthread_t* producers = new pthread_t[num_producers];
pthread_t* consumers = new pthread_t[num_consumers];

pthread_mutex_init(&mutex, NULL);
sem_init(&empty_slots, 0, MAX_BUFFER_SIZE); // Initialize empty
slots to max size
sem_init(&filled_slots, 0, 0); // Initialize filled slots to 0

// Create producer threads
for (long i = 0; i < num_producers; i++) {

pthread_create(&producers[i], NULL, producer, (void*)i);
}

// Create consumer threads
for (long i = 0; i < num_consumers; i++) {
pthread_create(&consumers[i], NULL, consumer, (void*)i);
}

// Wait for producer and consumer threads to finish
for (int i = 0; i < num_producers; i++) {
pthread_join(producers[i], NULL);
}
for (int i = 0; i < num_consumers; i++) {
pthread_join(consumers[i], NULL);
}

// Cleanup
pthread_mutex_destroy(&mutex);
sem_destroy(&empty_slots);
sem_destroy(&filled_slots);

std::cout << "All production and consumption operations
completed." << std::endl;

delete[] producers;
delete[] consumers;

return 0;
}

Output:
