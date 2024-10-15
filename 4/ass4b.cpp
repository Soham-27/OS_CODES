#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int read_count = 0; // Number of active readers
pthread_mutex_t read_mutex; // Mutex for readers
sem_t write_sem; // Semaphore for writers

// Total number of operations
int total_read_ops = 0;
int total_write_ops = 0;

// Reader function
void* reader(void* param) {
long reader_id = (long)param;
int read_ops = 0; // Count of read operations for this reader

while (read_ops < total_read_ops) {
pthread_mutex_lock(&read_mutex); // Lock for updating
read_count
read_count++;
if (read_count == 1) {
// Block writers if this is the first reader
sem_wait(&write_sem);
}
pthread_mutex_unlock(&read_mutex);

// Reading section
std::cout << "Reader " << reader_id << " is reading..." <<
std::endl;

sleep(1); // Simulate reading
read_ops++;

pthread_mutex_lock(&read_mutex); // Lock for updating
read_count
read_count--;
if (read_count == 0) {
// Allow writers if this is the last reader
sem_post(&write_sem);
}
pthread_mutex_unlock(&read_mutex);

sleep(1); // Simulate time between reads
}

return NULL;
}

// Writer function
void* writer(void* param) {
long writer_id = (long)param;
int write_ops = 0; // Count of write operations for this writer

while (write_ops < total_write_ops) {
sem_wait(&write_sem); // Request exclusive access

// Writing section
std::cout << "Writer " << writer_id << " is writing..." <<
std::endl;
sleep(2); // Simulate writing
write_ops++;

sem_post(&write_sem); // Release exclusive access

// Notify readers that writing has finished
std::cout << "Writer " << writer_id << " has finished
writing." << std::endl;
sleep(1); // Simulate time between writes
}

return NULL;
}

int main() {
int num_readers, num_writers;

std::cout << "Enter the number of readers: ";
std::cin >> num_readers;
std::cout << "Enter the number of writers: ";
std::cin >> num_writers;
std::cout << "Enter the number of read operations per reader: ";
std::cin >> total_read_ops;
std::cout << "Enter the number of write operations per writer:
";
std::cin >> total_write_ops;

pthread_t* readers = new pthread_t[num_readers];
pthread_t* writers = new pthread_t[num_writers];

pthread_mutex_init(&read_mutex, NULL);
sem_init(&write_sem, 0, 1); // Initialize semaphore for writers

// Create reader and writer threads
for (long i = 0; i < num_readers; i++) {
pthread_create(&readers[i], NULL, reader, (void*)i);
}

for (long i = 0; i < num_writers; i++) {
pthread_create(&writers[i], NULL, writer, (void*)i);
}

// Wait for reader and writer threads to finish
for (int i = 0; i < num_readers; i++) {
pthread_join(readers[i], NULL);
}
for (int i = 0; i < num_writers; i++) {
pthread_join(writers[i], NULL);
}

// Cleanup
pthread_mutex_destroy(&read_mutex);
sem_destroy(&write_sem);

std::cout << "All read and write operations completed." <<
std::endl;

delete[] readers;
delete[] writers;

return 0;
}

Output:
