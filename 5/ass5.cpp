#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10 // Maximum processes
#define MAX_R 10 // Maximum resources

void calculateNeed(int need[MAX_P][MAX_R], int max[MAX_P][MAX_R],
int allot[MAX_P][MAX_R], int p, int r) {
for (int i = 0; i < p; i++)
for (int j = 0; j < r; j++)
need[i][j] = max[i][j] - allot[i][j];
}

bool isSafe(int processes[], int avail[], int max[MAX_P][MAX_R], int
allot[MAX_P][MAX_R], int p, int r) {
int need[MAX_P][MAX_R];
calculateNeed(need, max, allot, p, r);

bool finish[MAX_P] = {false};
int safeSeq[MAX_P];
int work[MAX_R];

for (int i = 0; i < r; i++)
work[i] = avail[i];

int count = 0;
while (count < p) {
bool found = false;
for (int pIndex = 0; pIndex < p; pIndex++) {
if (!finish[pIndex]) {
int j;

for (j = 0; j < r; j++)
if (need[pIndex][j] > work[j])
break;

if (j == r) {
for (int k = 0; k < r; k++)
work[k] += allot[pIndex][k];

safeSeq[count++] = pIndex;
finish[pIndex] = true;
found = true;
}
}
}

if (!found) {
printf("System is not in a safe state.\n");
return false;
}
}

printf("System is in a safe state.\nSafe sequence is: ");
for (int i = 0; i < p; i++)
printf("P%d ", safeSeq[i]);
printf("\n");
return true;
}

int main() {
int processes[MAX_P];
int avail[MAX_R];
int max[MAX_P][MAX_R];

int allot[MAX_P][MAX_R];
int p, r;

printf("Enter the number of processes (max 10): ");
scanf("%d", &p);
printf("Enter the number of resources (max 10): ");
scanf("%d", &r);

printf("Enter the available resources: ");
for (int i = 0; i < r; i++)
scanf("%d", &avail[i]);

printf("Enter the maximum resource allocation for each
process:\n");
for (int i = 0; i < p; i++) {
processes[i] = i;
printf("Process P%d: ", i);
for (int j = 0; j < r; j++)
scanf("%d", &max[i][j]);
}

printf("Enter the currently allocated resources for each
process:\n");
for (int i = 0; i < p; i++) {
printf("Process P%d: ", i);
for (int j = 0; j < r; j++)
scanf("%d", &allot[i][j]);
}

isSafe(processes, avail, max, allot, p, r);
return 0;
}
