#include <stdio.h>
// Function to display matrices in a table format
void displayMatrices(int allot[][10], int max[][10], int need[][10], int n, int m) {
printf("\n%-10s%-15s%-15s%-15s\n", "Process", "Allocation", "Max", "Need");
printf("-------------------------------------------------------------\n");
for (int i = 0; i < n; i++) {
printf("P%-9d", i);
// Print Allocation matrix
for (int j = 0; j < m; j++) {
printf("%d ", allot[i][j]);
}
printf("\t");
// Print Max matrix
for (int j = 0; j < m; j++) {
printf("%d ", max[i][j]);
}
printf("\t\t");
// Print Need matrix
for (int j = 0; j < m; j++) {
printf("%d ", need[i][j]);
}
printf("\n");
}
}
// Function to calculate the Need matrix and display all matrices
void calculateNeed(int need[][10], int max[][10], int allot[][10], int n, int m) {
// Calculate Need matrix: Need[i][j] = Max[i][j] - Allocation[i][j]
for (int i = 0; i < n; i++) {
for (int j = 0; j < m; j++) {
need[i][j] = max[i][j] - allot[i][j];
}
}
// Display matrices in tabular format
displayMatrices(allot, max, need, n, m);
}

// Function to check if the system is in a safe state
int isSafe(int processes[], int avail[], int max[][10], int allot[][10], int need[][10], int n, int m) {
int finish[n], safeSeq[n], work[m];
for (int i = 0; i < n; i++) {
finish[i] = 0;
}
for (int i = 0; i < m; i++) {
work[i] = avail[i];
}
int count = 0;
while (count < n) {
int found = 0;
for (int p = 0; p < n; p++) {
if (finish[p] == 0) {
int j;
for (j = 0; j < m; j++) {
if (need[p][j] > work[j]) {
break;
}
}
// If all resources can be allocated
if (j == m) {
// Simulate resource release by adding allocated resources to available (work)
for (int k = 0; k < m; k++) {
work[k] += allot[p][k];
}
safeSeq[count++] = p;
finish[p] = 1;
found = 1;
}
}
}
// If no process was found in this round, system is not safe
if (found == 0) {
printf("\nSystem is not in a safe state.\n");
return 0;
}
}
// If all processes are finished, system is safe
printf("\nSystem is in a safe state.\nSafe sequence is: ");

for (int i = 0; i < n; i++) {
printf("P%d ", safeSeq[i]);
}
printf("\n");
return 1;
}
// Function to request resources
void requestResources(int processes[], int avail[], int max[][10], int allot[][10], int need[][10], int n,
int m) {
int req[m];
int process;
printf("\nEnter the process number (0 to %d): ", n - 1);
scanf("%d", &process);
printf("\nEnter the request for resources: \n");
for (int i = 0; i < m; i++) {
printf("Resource %d: ", i + 1);
scanf("%d", &req[i]);
}
// Check if request is valid
for (int i = 0; i < m; i++) {
if (req[i] > need[process][i]) {
printf("\nError: Process has exceeded its maximum claim.\n");
return;
}
}
// Check if resources are available
for (int i = 0; i < m; i++) {
if (req[i] > avail[i]) {
printf("\nError: Resources are not available.\n");
return;
}
}
// Temporarily allocate requested resources
for (int i = 0; i < m; i++) {
avail[i] -= req[i];
allot[process][i] += req[i];
need[process][i] -= req[i];
}

// Check if the system is in a safe state
if (isSafe(processes, avail, max, allot, need, n, m)) {
printf("\nResources allocated successfully.\n");
} else {
printf("\nSystem is unsafe after allocation. Rolling back request.\n");
for (int i = 0; i < m; i++) {
avail[i] += req[i];
allot[process][i] -= req[i];
need[process][i] += req[i];
}
}
}
int main() {
int n, m;
printf("\nEnter the number of processes: ");
scanf("%d", &n);
printf("Enter the number of resource types: ");
scanf("%d", &m);
int processes[n];
for (int i = 0; i < n; i++) {
processes[i] = i;
}
int avail[m];
printf("Enter the available resources (one for each type): ");
for (int i = 0; i < m; i++) {
scanf("%d", &avail[i]);
}
int max[n][10], allot[n][10], need[n][10];
printf("\nEnter the allocated resources for each process:\n");
for (int i = 0; i < n; i++) {
printf("Process %d: ", i);
for (int j = 0; j < m; j++) {
scanf("%d", &allot[i][j]);
}
}
printf("\nEnter the maximum resources needed by each process:\n");
for (int i = 0; i < n; i++) {

printf("Process %d: ", i);
for (int j = 0; j < m; j++) {
scanf("%d", &max[i][j]);
}
}
int choice;
while (1) {
printf("\nMenu:\n");
printf("1. Calculate Need matrix and display Allocation, Max, and Need matrices\n");
printf("2. Check System Safety and Write Safe Sequence\n");
printf("3. Request Resources\n");
printf("4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
calculateNeed(need, max, allot, n, m);
break;
case 2:
isSafe(processes, avail, max, allot, need, n, m);
break;
case 3:
requestResources(processes, avail, max, allot, need, n, m);
break;
case 4:
printf("\nExiting the program.\n");
return 0;
default:
printf("\nInvalid choice! Please try again.\n");
}
}
return 0;
}
