#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sortByArrival(vector<string>& pid, vector<int>& at, vector<int>& bt, vector<bool>& flag, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
                swap(flag[j], flag[j + 1]);
            }
        }
    }
}

void calculateSJF(vector<string>& pid, vector<int>& at, vector<int>& bt, vector<int>& ct, vector<int>& tat, vector<int>& wt, vector<bool>& flag, int n) {
    int ncp = 0, currTime = 0, minIdx;
    cout << "\nGantt Chart:\n ";

    while (ncp < n) {
        minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (!flag[i] && at[i] <= currTime) {
                if (minIdx == -1 || bt[i] < bt[minIdx]) {
                    minIdx = i;
                }
            }
        }

        if (minIdx == -1) {
            cout << "-- ";
            currTime++;
        } else {
            cout << pid[minIdx] << " ";
            ct[minIdx] = currTime + bt[minIdx];
            tat[minIdx] = ct[minIdx] - at[minIdx];
            wt[minIdx] = tat[minIdx] - bt[minIdx];
            flag[minIdx] = true;
            ncp++;
            currTime = ct[minIdx];
        }
    }

    cout << "\n";
    currTime = 0;
    cout << "0";
    for (int i = 0; i < n; i++) {
        if (currTime < at[i]) {
            for (int j = currTime; j < at[i]; j++) cout << " ";
            cout << at[i];
            currTime = at[i];
        }
        for (int j = 0; j < bt[i]; j++) cout << " ";
        cout << ct[i];
        currTime = ct[i];
    }
    cout << "\n";
}

void printProcesses(const vector<string>& pid, const vector<int>& at, const vector<int>& bt, const vector<int>& ct, const vector<int>& tat, const vector<int>& wt, int n) {
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t"
             << ct[i] << "\t\t" << tat[i] << "\t\t" << wt[i] << "\n";
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<string> pid(n);
    vector<int> at(n), bt(n), ct(n), tat(n), wt(n);
    vector<bool> flag(n, false);

    for (int i = 0; i < n; i++) {
        cout << "Enter the process ID of Process " << i + 1 << ": ";
        cin >> pid[i];
        cout << "Enter the arrival time and burst time for process " << pid[i] << ": ";
        cin >> at[i] >> bt[i];
    }

    sortByArrival(pid, at, bt, flag, n);
    calculateSJF(pid, at, bt, ct, tat, wt, flag, n);
    printProcesses(pid, at, bt, ct, tat, wt, n);

    return 0;
}
