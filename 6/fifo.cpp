#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to check if a page is in memory
bool isPageInMemory(const vector<int>& frames, int page) {
for (int frame : frames) {
if (frame == page) {
return true;
}
}
return false;
}

// FIFO Page Replacement Algorithm
int FIFOPageReplacement(const vector<int>& pages, int numFrames) {
vector<int> frames; // Vector to store pages in memory
queue<int> fifoQueue; // Queue to track the order of page
insertion
int pageFaults = 0; // Count of page faults

for (int page : pages) {
// If the page is not in memory
if (!isPageInMemory(frames, page)) {
// If there is space in memory
if (frames.size() < numFrames) {
frames.push_back(page); // Add new page to memory
} else {

// Replace the oldest page (FIFO)
int pageToReplace = fifoQueue.front();
fifoQueue.pop(); // Remove the oldest page from the
queue

// Find and remove the page from the frames
for (int i = 0; i < frames.size(); i++) {
if (frames[i] == pageToReplace) {
frames[i] = page; // Replace old page with
new page
break;
}
}
}

// Add the new page to the FIFO queue and increment page
faults
fifoQueue.push(page);
pageFaults++;
}

// Print the current state of the frames
cout << "Frames after accessing page " << page << ": ";
for (int frame : frames) {
cout << frame << " ";
}
cout << endl;
}

return pageFaults; // Return total page faults
}

int main() {
int numFrames, numPages;

// Get the number of frames
cout << "Enter the number of frames: ";
cin >> numFrames;

// Get the number of pages
cout << "Enter the number of pages in the reference string: ";
cin >> numPages;

vector<int> pages(numPages); // Vector for pages

// Get the reference string
cout << "Enter the reference string: ";
for (int i = 0; i < numPages; i++) {
cin >> pages[i];
}

// Perform FIFO page replacement
int pageFaults = FIFOPageReplacement(pages, numFrames);

// Print total page faults
cout << "Total page faults: " << pageFaults << endl;

return 0;
}
