#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Function to compare two integers, used for sorting in qsort
int compare(const void *a, const void *b) {
return (*(int *)a - *(int *)b); // for ascending order sorting
}
int choice, track, no_req, head1;
int diskRequired[100];
// Shortest Seek Time First (SSTF)
void sstf(int requests[], int n, int head) {
int i, j, min_seek_time, next_request, current, total_seek = 0;
int completed[100] = {0};
int seek_sequence[100];
int sequence_index = 0;
current = head;
seek_sequence[sequence_index++] = current;
printf("\nSSTF Seek sequence: \n");
printf("%d ", current);
for (i = 0; i < n; i++) {
min_seek_time = 1e9;
next_request = -1;
for (j = 0; j < n; j++) {
if (!completed[j]) {
int seek_time = abs(requests[j] - current);
if (seek_time < min_seek_time) {
min_seek_time = seek_time;
next_request = j;
}
}
}

if (next_request == -1) break;
current = requests[next_request];
seek_sequence[sequence_index++] = current;
total_seek += min_seek_time;
completed[next_request] = 1;
printf("%d ", current);
}
printf("\nTotal seek time: %d\n", total_seek);
}
// SCAN algorithm
void scan(int requests[], int n, int head, int track_size) {
int i, total_seek = 0, current = head;
int index = 0;
for (i = 0; i < n; i++) {
if (head < requests[i]) {
index = i;
break;
}
}
printf("\nSCAN Seek sequence: \n");
// Moving right
for (i = index; i < n; i++) {
printf("%d ", requests[i]);
total_seek += abs(current - requests[i]);
current = requests[i];
}
printf("%d ", track_size - 1);
total_seek += abs(current - (track_size - 1));
current = track_size - 1;
for (i = index - 1; i >= 0; i--) {
printf("%d ", requests[i]);
total_seek += abs(current - requests[i]);
current = requests[i];
}

printf("\nTotal seek time: %d\n", total_seek);
}
// C-LOOK algorithm
void c_look(int requests[], int n, int head) {
int i, total_seek = 0, current = head;
int index = 0;
for (i = 0; i < n; i++) {
if (head < requests[i]) {
index = i;
break;
}
}
printf("\nC-LOOK Seek sequence: \n");
// Moving right
for (i = index; i < n; i++) {
printf("%d ", requests[i]);
total_seek += abs(current - requests[i]);
current = requests[i];
}
// Jump to the first request in the sequence
if (index > 0) {
total_seek += abs(current - requests[0]);
current = requests[0];
for (i = 0; i < index; i++) {
printf("%d ", requests[i]);
total_seek += abs(current - requests[i]);
current = requests[i];
}
}
printf("\nTotal seek time: %d\n", total_seek);
}
int main() {
printf("\nEnter total number of tracks: ");
scanf("%d", &track);
printf("Enter total number of disk requests: ");
scanf("%d", &no_req);
printf("Enter disk requests: ");

for (int i = 0; i < no_req; i++) {
scanf("%d", &diskRequired[i]);
}
qsort(diskRequired, no_req, sizeof(int), compare);
printf("\nEnter current head position: ");
scanf("%d", &head1);
while (1) {
printf("\nMenu: \n");
printf("\n1. SSTF\n");
printf("2. SCAN\n");
printf("3. C-LOOK\n");
printf("4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
sstf(diskRequired, no_req, head1);
printf("\n--------------------------------------------------------------------\n");
break;
case 2:
scan(diskRequired, no_req, head1, track);
printf("\n--------------------------------------------------------------------\n");
break;
case 3:
c_look(diskRequired, no_req, head1);
printf("\n--------------------------------------------------------------------\n");
break;
case 4:
exit(0);
break;
default:
printf("\nEnter a valid choice: ");
}
}
return 0;
}
