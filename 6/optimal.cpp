#include <bits/stdc++.h>
using namespace std;

// Function to find the page to replace based on future references
int findOptimal(const vector<int>& v, const vector<int>& future, int
currentIndex) {
int farthest = currentIndex;
int indexToReplace = -1;

// Check each page in the memory
for (int i = 0; i < v.size(); i++) {
int page = v[i];
bool foundInFuture = false;

// Check when this page will be used next in the future
for (int j = currentIndex + 1; j < future.size(); j++) {
if (future[j] == page) {
foundInFuture = true;
if (j > farthest) {
farthest = j;

indexToReplace = i; // Replace the page that is
used farthest
}
break;
}
}

// If the page is never used again in the future, replace it
immediately
if (!foundInFuture) {
return i;
}
}

// If all pages will be used again, return the one that is
farthest
if (indexToReplace == -1) {
return 0; // If none of the pages are found in the future,
replace the first one
}
return indexToReplace;
}
int main() {
vector<int> v; // Vector to represent pages in memory
vector<int> future; // Store the page requests to simulate
future reference
int next;

// Read the sequence of page references
cout << "Enter the page reference sequence (end with -1):" <<
endl;
while (cin >> next && next != -1) {
future.push_back(next);
}

// Memory size: assume 3-page memory for the example
int memorySize = 3;

// Process each page in the reference sequence
for (int i = 0; i < future.size(); i++) {
int page = future[i];

// Check if the page is already in memory
if (find(v.begin(), v.end(), page) != v.end()) {
cout << "Page " << page << " already in memory." <<
endl;
} else {
// If the memory is full, replace the optimal page
if (v.size() == memorySize) {
int indexToReplace = findOptimal(v, future, i);
cout << "Page fault! Replacing page " <<
v[indexToReplace] << " with " << page << "." << endl;
v[indexToReplace] = page;
} else {
// If there's still space in memory, just add the
page
cout << "Page fault! Adding page " << page << " to
memory." << endl;
v.push_back(page);
}
}
// Print current memory state
cout << "Memory: ";
for (int j = 0; j < v.size(); j++) {
cout << v[j] << " ";
}
cout << endl;
} return 0;
}
