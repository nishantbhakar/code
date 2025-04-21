#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void displayTable(const vector<int>& processes, const vector<int>& allocation, const vector<int>& fragments){
    cout << "\n+---------+---------------+-----------+-----------+\n";
    cout << "| Process | Process Size | Block No  | Fragment  |\n";
    cout << "+---------+---------------+-----------+-----------+\n";

    for (size_t i = 0; i < processes.size(); i++) {
        cout << "| "
             << setw(7) << i + 1 << " | "
             << setw(13) << processes[i] << " | "
             << setw(9) << (allocation[i] != -1 ? to_string(allocation[i] + 1) : "N/A") << " | "
             << setw(9) << (allocation[i] != -1 ? to_string(fragments[i]) : "-") << " |\n";
    }

    cout << "+---------+---------------+-----------+-----------+\n";
}

void firstFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1), fragments(processes.size(), 0);
    for (size_t i = 0; i < processes.size(); i++) {
        for (size_t j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                fragments[i] = blocks[j] - processes[i];
                blocks[j] -= processes[i];
                break;
            }
        }
    }
    cout << "\n--- First Fit Allocation ---";
    displayTable(processes, allocation, fragments);
}

void bestFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1), fragments(processes.size(), 0);
    for (size_t i = 0; i < processes.size(); i++) {
        int bestIdx = -1;
        for (size_t j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i] && (bestIdx == -1 || blocks[j] < blocks[bestIdx])) {
                bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            fragments[i] = blocks[bestIdx] - processes[i];
            blocks[bestIdx] -= processes[i];
        }
    }
    cout << "\n--- Best Fit Allocation ---";
    displayTable(processes, allocation, fragments);
}

void worstFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1), fragments(processes.size(), 0);
    for (size_t i = 0; i < processes.size(); i++) {
        int worstIdx = -1;
        for (size_t j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i] && (worstIdx == -1 || blocks[j] > blocks[worstIdx])) {
                worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            fragments[i] = blocks[worstIdx] - processes[i];
            blocks[worstIdx] -= processes[i];
        }
    }
    cout << "\n--- Worst Fit Allocation ---";
    displayTable(processes, allocation, fragments);
}

void nextFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1), fragments(processes.size(), 0);
    int lastAllocated = 0;
    for (size_t i = 0; i < processes.size(); i++) {
        size_t j = lastAllocated;
        bool allocated = false;
        do {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                fragments[i] = blocks[j] - processes[i];
                blocks[j] -= processes[i];
                lastAllocated = j;
                allocated = true;
                break;
            }
            j = (j + 1) % blocks.size();
        } while (j != lastAllocated);
    }
    cout << "\n--- Next Fit Allocation ---";
    displayTable(processes, allocation, fragments);
}

int main() {
    int numBlocks, numProcesses;

    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;
    vector<int> originalBlocks(numBlocks);
    cout << "Enter block sizes: ";
    for (int& block : originalBlocks) cin >> block;

    cout << "Enter number of processes: ";
    cin >> numProcesses;
    vector<int> processes(numProcesses);
    cout << "Enter process sizes: ";
    for (int& process : processes) cin >> process;

    int choice;
    do {
        cout << "\nMemory Allocation Techniques:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        vector<int> blocks = originalBlocks;

        switch (choice) {
            case 1:
                firstFit(blocks, processes);
                break;
            case 2:
                bestFit(blocks, processes);
                break;
            case 3:
                worstFit(blocks, processes);
                break;
            case 4:
                nextFit(blocks, processes);
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}