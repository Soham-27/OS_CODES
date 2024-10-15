#include <stdio.h>
#include <stdlib.h>

void SSTF(int requests[], int n, int head) {
int total_movement = 0;
int completed[n], sequence[n];
int min_index, min_distance;

for (int i = 0; i < n; i++) {
completed[i] = 0;
}

for (int i = 0; i < n; i++) {
min_distance = 1000;
for (int j = 0; j < n; j++) {
if (!completed[j] && abs(requests[j] - head) <
min_distance) {
min_distance = abs(requests[j] - head);
min_index = j;
}
}
sequence[i] = requests[min_index];
total_movement += abs(requests[min_index] - head);
head = requests[min_index];
completed[min_index] = 1;
}

printf("\nSSTF sequence of requests: ");
for (int i = 0; i < n; i++) {
printf("%d ", sequence[i]);

}
printf("\nTotal head movement (SSTF): %d\n", total_movement);
}

void SCAN(int requests[], int n, int head, int disk_size) {
int total_movement = 0, direction;
int sequence[n + 1], sequence_count = 0;
int i;

printf("\nChoose direction: 0 (downwards) or 1 (upwards): ");
scanf("%d", &direction);

// Sort requests
for (int i = 0; i < n - 1; i++) {
for (int j = i + 1; j < n; j++) {
if (requests[i] > requests[j]) {
int temp = requests[i];
requests[i] = requests[j];
requests[j] = temp;
}
}
}

if (direction == 1) {
for (i = 0; i < n; i++) {
if (requests[i] > head) break;
}
// Serve requests moving upwards
for (int j = i; j < n; j++) {
sequence[sequence_count++] = requests[j];
total_movement += abs(requests[j] - head);
head = requests[j];

}
// Serve requests moving downwards
total_movement += abs(disk_size - 1 - head);
head = disk_size - 1;
for (int j = i - 1; j >= 0; j--) {
sequence[sequence_count++] = requests[j];
total_movement += abs(requests[j] - head);
head = requests[j];
}
} else {
for (i = n - 1; i >= 0; i--) {
if (requests[i] < head) break;
}
// Serve requests moving downwards
for (int j = i; j >= 0; j--) {
sequence[sequence_count++] = requests[j];
total_movement += abs(requests[j] - head);
head = requests[j];
}
// Serve requests moving upwards
total_movement += abs(head - 0);
head = 0;
for (int j = i + 1; j < n; j++) {
sequence[sequence_count++] = requests[j];
total_movement += abs(requests[j] - head);
head = requests[j];
}
}

printf("\nSCAN sequence of requests: ");
for (int i = 0; i < sequence_count; i++) {
printf("%d ", sequence[i]);

}
printf("\nTotal head movement (SCAN): %d\n", total_movement);
}
void C_LOOK(int requests[], int n, int head) {
int total_movement = 0;
int sequence[n], sequence_count = 0;
int i;

// Sort requests
for (int i = 0; i < n - 1; i++) {
for (int j = i + 1; j < n; j++) {
if (requests[i] > requests[j]) {
int temp = requests[i];
requests[i] = requests[j];
requests[j] = temp;
}
}
}
for (i = 0; i < n; i++) {
if (requests[i] > head) break;
}
// Serve requests moving upwards
for (int j = i; j < n; j++) {
sequence[sequence_count++] = requests[j];
total_movement += abs(requests[j] - head);
head = requests[j];
}
// Jump to the lowest request
total_movement += abs(head - requests[0]);
head = requests[0];
// Serve remaining requests
for (int j = 0; j < i; j++) {

sequence[sequence_count++] = requests[j];
total_movement += abs(requests[j] - head);
head = requests[j];
}
printf("\nC-LOOK sequence of requests: ");
for (int i = 0; i < sequence_count; i++) {
printf("%d ", sequence[i]);
}
printf("\nTotal head movement (C-LOOK): %d\n", total_movement);
}

int main() {
int n, head, disk_size;
printf("Enter the number of requests: ");
scanf("%d", &n);

int requests[n];
printf("Enter the requests: ");
for (int i = 0; i < n; i++) {
scanf("%d", &requests[i]);
}
printf("Enter the initial head position: ");
scanf("%d", &head);
printf("Enter disk size (maximum track number): ");
scanf("%d", &disk_size);

SSTF(requests, n, head);
SCAN(requests, n, head, disk_size);
C_LOOK(requests, n, head);

return 0;
}
