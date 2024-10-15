#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

// Function to check if a page is present in the frame
bool isPresent(int frame[], int n, int size) {
    for (int i = 0; i < size; i++) {
        if (frame[i] == n) {
            return true;
        }
    }
    return false;
}

// FIFO Page Replacement Algorithm
void fifo(int *sequence, int seqLength, int frameSize) {
    int *frame = (int *)malloc(frameSize * sizeof(int));
    if (frame == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
    }

    int count = 0; // page fault count
    int hits = 0;  // hit count
    int first_index = 0;
    
    for (int i = 0; i < seqLength; i++) {
        if (!isPresent(frame, sequence[i], frameSize)) {
            frame[first_index] = sequence[i];
            first_index = (first_index + 1) % frameSize;
            count++; // page fault
        } else {
            hits++; // page hit
        }

        // Print current frame state
        printf("FIFO Frame: ");
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == -1) {
                printf(" ");
            } else {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");
    }

    // Calculate hit and miss ratios
    double hitRatio = (double)hits / seqLength;
    double missRatio = (double)count / seqLength;

    printf("\nTotal number of page faults (FIFO) = %d\n", count);
    printf("Hit Ratio = %.2f, Miss Ratio = %.2f\n", hitRatio, missRatio);
    free(frame); // Free allocated memory
}

// LRU Page Replacement Algorithm
void lru(int *sequence, int seqLength, int frameSize) {
    int *frame = (int *)malloc(frameSize * sizeof(int));
    int *lastUsed = (int *)malloc(frameSize * sizeof(int));
    if (frame == NULL || lastUsed == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < frameSize; i++) frame[i] = -1;
    for (int i = 0; i < frameSize; i++) lastUsed[i] = -1;

    int count = 0; // page fault count
    int hits = 0;  // hit count

    for (int i = 0; i < seqLength; i++) {
        int page = sequence[i];

        // Check if the page is already present in the frame
        if (isPresent(frame, page, frameSize)) {
            // Page hit
            hits++;
            for (int j = 0; j < frameSize; j++) {
                if (frame[j] == page) {
                    lastUsed[j] = i;
                }
            }
        } else {
            // Page fault
            int index;
            if (i >= frameSize) {
                int min = lastUsed[0];
                index = 0;
                for (int j = 1; j < frameSize; j++) {
                    if (lastUsed[j] < min) {
                        min = lastUsed[j];
                        index = j;
                    }
                }
            } else {
                index = i;
            }
            frame[index] = page;
            lastUsed[index] = i;
            count++; // page fault
        }

        // Print current frame state
        printf("LRU Frame: ");
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == -1) {
                printf(" ");
            } else {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");
    }

    // Calculate hit and miss ratios
    double hitRatio = (double)hits / seqLength;
    double missRatio = (double)count / seqLength;

    printf("\nTotal number of page faults (LRU) = %d\n", count);
    printf("Hit Ratio = %.2f, Miss Ratio = %.2f\n", hitRatio, missRatio);
    free(frame); // Free allocated memory
    free(lastUsed); // Free allocated memory
}

// Optimal Page Replacement Algorithm
int optimalPageReplacement(int *frame, int *pageSequence, int pageIndex, int size, int sequenceLength) {
    int farthest = pageIndex;
    int index = -1;
    for (int i = 0; i < size; i++) {
        int j;
        for (j = pageIndex; j < sequenceLength; j++) {
            if (frame[i] == pageSequence[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == sequenceLength) {
            return i;
        }
    }
    if (index == -1) {
        index = 0;
    }
    return index;
}

void optimal(int *sequence, int seqLength, int frameSize) {
    int *frame = (int *)malloc(frameSize * sizeof(int));

    if (frame == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < frameSize; i++) frame[i] = -1;

    int count = 0; // page fault count
    int hits = 0;  // hit count

    for (int i = 0; i < seqLength; i++) {
        int page = sequence[i];

        // Check if the page is already present in the frame
        if (isPresent(frame, page, frameSize)) {
            hits++; // page hit
            continue;
        } else {
            // Page fault
            int index;
            if (i < frameSize) {
                index = i;
            } else {
                // Find the page to replace
                index = optimalPageReplacement(frame, sequence, i + 1, frameSize, seqLength);
            }
            frame[index] = page;
            count++; // page fault
        }

        // Print current frame state
        printf("Optimal Frame: ");
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == -1) {
                printf(" ");
            } else {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");
    }

    // Calculate hit and miss ratios
    double hitRatio = (double)hits / seqLength;
    double missRatio = (double)count / seqLength;

    printf("\nTotal number of page faults (Optimal) = %d\n", count);
    printf("Hit Ratio = %.2f, Miss Ratio = %.2f\n", hitRatio, missRatio);
    free(frame); // Free allocated memory
}

int main() {
    int choice;
    int frameSize, seqLength;

    while (1) {
        printf("\nPage Replacement Algorithms:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            printf("Exited Successfully!");
            return 0;
        }

        printf("\nEnter frame size (minimum 3): ");
        scanf("%d", &frameSize);
        if (frameSize < 3) {
            printf("Frame size must be at least 3.\n");
            continue;
        }

        printf("Enter length of page sequence: ");
        scanf("%d", &seqLength);
        int *sequence = (int *)malloc(seqLength * sizeof(int));
        if (sequence == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        printf("Enter page sequence:\n");
        for (int i = 0; i < seqLength; i++) {
            scanf("%d", &sequence[i]);
        }

        switch (choice) {
            case 1:
                fifo(sequence, seqLength, frameSize);
                printf("\n------------------------------------------------------------\n");
                break;
            case 2:
                lru(sequence, seqLength, frameSize);
                printf("\n------------------------------------------------------------\n");
                break;
            case 3:
                optimal(sequence, seqLength, frameSize);
                printf("\n------------------------------------------------------------\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }

        free(sequence); // Free allocated memory
    }

    return 0;
}

