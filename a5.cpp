#include <iostream> 
#include <vector> 
#include <limits> 
using namespace std; 

class BankersAlgorithm { 
private: 
    int processes; 
    int resources; 
    vector<vector<int>> allocation; 
    vector<vector<int>> maximum; 
    vector<vector<int>> need; 
    vector<int> available; 

public: 
    BankersAlgorithm(int p, int r, vector<vector<int>> alloc, vector<vector<int>> max, vector<int> avail) 
    : processes(p), resources(r), allocation(alloc), maximum(max), available(avail) { 
        need.resize(processes, vector<int>(resources, 0)); 
        for (int i = 0; i < processes; i++) { 
            for (int j = 0; j < resources; j++) { 
                need[i][j] = maximum[i][j] - allocation[i][j]; 
            } 
        } 
    } 

    bool isSafe() { 
        vector<int> work = available; 
        vector<bool> finish(processes, false); 
        vector<int> safeSequence; 
        int count = 0; 

        while (count < processes) { 
            bool found = false; 
            for (int i = 0; i < processes; i++) { 
                if (!finish[i]) { 
                    bool canExecute = true; 
                    for (int j = 0; j < resources; j++) { 
                        if (need[i][j] > work[j]) { 
                            canExecute = false; 
                            break; 
                        } 
                    } 
                    if (canExecute) { 
                        for (int j = 0; j < resources; j++) { 
                            work[j] += allocation[i][j]; 
                        } 
                        finish[i] = true; 
                        safeSequence.push_back(i); 
                        found = true; 
                        count++; 
                    } 
                } 
            } 
            if (!found) { 
                cout << "System is in an unsafe state!" << endl; 
                return false; 
            } 
        } 

        cout << "System is in a safe state.\nSafe sequence: "; 
        for (int i : safeSequence) { 
            cout << "P" << i << " "; 
        } 
        cout << endl; 
        return true; 
    } 
}; 

int getValidatedInput(const string &prompt) { 
    int value; 
    while (true) { 
        cout << prompt; 
        cin >> value; 
        if (cin.fail()) { 
            cout << "Invalid input! Please enter a valid integer.\n"; 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else if (value < 0) { 
            cout << "Error: Value must be non-negative.\n"; 
        } else { 
            return value; 
        } 
    } 
} 

int main() { 
    int processes = getValidatedInput("Enter the number of processes: "); 
    int resources = getValidatedInput("Enter the number of resource types: "); 

    vector<vector<int>> allocation(processes, vector<int>(resources)); 
    vector<vector<int>> maximum(processes, vector<int>(resources)); 
    vector<int> available(resources); 

    cout << "Enter the allocation matrix:\n"; 
    for (int i = 0; i < processes; i++) { 
        for (int j = 0; j < resources; j++) { 
            allocation[i][j] = getValidatedInput("Allocation for P" + to_string(i) + ", Resource " + to_string(j) + ": "); 
        } 
    } 

    cout << "Enter the maximum matrix:\n"; 
    for (int i = 0; i < processes; i++) { 
        for (int j = 0; j < resources; j++) { 
            while (true) { 
                maximum[i][j] = getValidatedInput("Maximum for P" + to_string(i) + ", Resource " + to_string(j) + ": "); 
                if (maximum[i][j] >= allocation[i][j]) { 
                    break; 
                } 
                cout << "Error: Maximum cannot be less than allocated resources.\n"; 
            } 
        } 
    } 

    cout << "Enter the available resources:\n"; 
    for (int j = 0; j < resources; j++) { 
        available[j] = getValidatedInput("Available resource " + to_string(j) + ": "); 
    } 

    BankersAlgorithm ba(processes, resources, allocation, maximum, available); 
    ba.isSafe(); 

    return 0; 
}