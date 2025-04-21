#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to print frame content vertically
void displayVerticalFrames(const vector<int>& frames) {
    cout << "Block State:\n";
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i] == -1)
            cout << "-\n";
        else
            cout << frames[i] << "\n";
    }
    cout << "----------------------\n";
}

// FCFS Page Replacement
int fcfs(const vector<int>& pages, int frameSize) {
    vector<int> frames(frameSize, -1);
    int pointer = 0, faults = 0;

    cout << "\n--- FCFS Page Replacement ---\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        cout << "Page " << page << " -> ";
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            frames[pointer] = page;
            pointer = (pointer + 1) % frameSize;
            faults++;
            cout << "Page Fault\n";
        } else {
            cout << "Hit\n";
        }
        displayVerticalFrames(frames);
    }
    cout << "Total Page Faults (FCFS): " << faults << "\n";
    return faults;
}

// LRU Page Replacement
int lru(const vector<int>& pages, int frameSize) {
    vector<int> frames;
    vector<int> recent;
    int faults = 0;

    cout << "\n--- LRU Page Replacement ---\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        cout << "Page " << page << " -> ";

        auto it = find(frames.begin(), frames.end(), page);
        if (it == frames.end()) {
            if (frames.size() < frameSize) {
                frames.push_back(page);
            } else {
                int lruPage = recent.front();
                int index = find(frames.begin(), frames.end(), lruPage) - frames.begin();
                frames[index] = page;
                recent.erase(recent.begin());
            }
            faults++;
            cout << "Page Fault\n";
        } else {
            cout << "Hit\n";
            recent.erase(remove(recent.begin(), recent.end(), page), recent.end());
        }
        recent.push_back(page);

        vector<int> filledFrames(frameSize, -1);
        for (int k = 0; k < frames.size(); k++)
            filledFrames[k] = frames[k];
        displayVerticalFrames(filledFrames);
    }
    cout << "Total Page Faults (LRU): " << faults << "\n";
    return faults;
}

// Optimal Page Replacement
int optimal(const vector<int>& pages, int frameSize) {
    vector<int> frames;
    int faults = 0;

    cout << "\n--- Optimal Page Replacement ---\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        cout << "Page " << page << " -> ";

        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            if (frames.size() < frameSize) {
                frames.push_back(page);
            } else {
                int replaceIdx = -1, farthest = i + 1;
                for (int j = 0; j < frames.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (pages[k] == frames[j]) break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        replaceIdx = j;
                    }
                    if (k == pages.size()) {
                        replaceIdx = j;
                        break;
                    }
                }
                if (replaceIdx == -1) replaceIdx = 0;
                frames[replaceIdx] = page;
            }
            faults++;
            cout << "Page Fault\n";
        } else {
            cout << "Hit\n";
        }

        vector<int> filledFrames(frameSize, -1);
        for (int k = 0; k < frames.size(); k++)
            filledFrames[k] = frames[k];
        displayVerticalFrames(filledFrames);
    }
    cout << "Total Page Faults (Optimal): " << faults << "\n";
    return faults;
}

int main() {
    int frameSize, numPages;
    cout << "Enter number of frames: ";
    cin >> frameSize;
    cout << "Enter number of pages: ";
    cin >> numPages;

    vector<int> pages(numPages);
    cout << "Enter " << numPages << " page numbers (space-separated): ";
    for (int i = 0; i < numPages; i++) {
        cin >> pages[i];
    }

    int fcfsFaults = fcfs(pages, frameSize);
    int lruFaults = lru(pages, frameSize);
    int optimalFaults = optimal(pages, frameSize);

    cout << "\n--- Result Summary ---\n";
    cout << "FCFS Faults: " << fcfsFaults << "\n";
    cout << "LRU Faults: " << lruFaults << "\n";
    cout << "Optimal Faults: " << optimalFaults << "\n";

    cout << "\nBest Algorithm: ";
    if (fcfsFaults <= lruFaults && fcfsFaults <= optimalFaults)
        cout << "FCFS (Page Faults: " << fcfsFaults << ")\n";
    else if (lruFaults <= fcfsFaults && lruFaults <= optimalFaults)
        cout << "LRU (Page Faults: " << lruFaults << ")\n";
    else
        cout << "Optimal (Page Faults: " << optimalFaults << ")\n";

    return 0;
}