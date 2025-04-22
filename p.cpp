#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sortByArrival(vector<string>& pid, vector<int>& at, vector<int>& bt, vector<int>& priority, vector<bool>& flag, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
                swap(priority[j], priority[j + 1]);
                swap(flag[j], flag[j + 1]);
            }
        }
    }
}

void prioritySchedule(vector<string>& pid, vector<int>& at, vector<int>& bt, vector<int>& priority, vector<int>& ct, vector<int>& tat, vector<int>& wt, vector<bool>& flag, int n) {
    int ncp = 0, currTime = 0, minIdx;
    vector<int> order(2 * n);
    vector<int> times(2 * n);
    int oi = 0;

    cout << "\nGantt Chart:\n";
    cout << " --------------------------------------\n";
    cout << "|";

    while (ncp < n) {
        minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (!flag[i] && at[i] <= currTime) {
                if (minIdx == -1 || priority[i] < priority[minIdx]) {
                    minIdx = i;
                }
            }
        }
        if (minIdx == -1) {
            int nextArrival = 99999;
            for (int i = 0; i < n; i++) {
                if (!flag[i] && at[i] > currTime && at[i] < nextArrival) {
                    nextArrival = at[i];
                }
            }
            cout << " I |";
            order[oi] = -1;
            currTime = nextArrival;
            times[oi++] = currTime;
        } else {
            cout << " " << pid[minIdx] << " |";
            ct[minIdx] = currTime + bt[minIdx];
            tat[minIdx] = ct[minIdx] - at[minIdx];
            wt[minIdx] = tat[minIdx] - bt[minIdx];
            flag[minIdx] = true;
            order[oi] = minIdx;
            currTime = ct[minIdx];
            times[oi++] = currTime;
            ncp++;
        }
    }

    cout << "\n --------------------------------------\n";
    cout << "0";
    for (int i = 0; i < oi; i++) {
        cout << " " << times[i];
    }
    cout << "\n";
}

void printProcesses(const vector<string>& pid, const vector<int>& at, const vector<int>& bt, const vector<int>& priority, const vector<int>& ct, const vector<int>& tat, const vector<int>& wt, int n) {
    float sum_wt = 0, sum_tat = 0;

    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << priority[i] << "\t\t" 
             << ct[i] << "\t\t" << tat[i] << "\t\t" << wt[i] << "\n";
        sum_wt += wt[i];
        sum_tat += tat[i];
    }
    cout << "\n\n";
    cout << "The average waiting time : " << (sum_wt / n) << endl;
    cout << "The average turn around time : " << (sum_tat / n) << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<string> pid(n);
    vector<int> at(n), bt(n), priority(n), ct(n), tat(n), wt(n);
    vector<bool> flag(n, false);

    for (int i = 0; i < n; i++) {
        cout << "Enter the process ID of Process " << i + 1 << ": ";
        cin >> pid[i];
        cout << "Enter the arrival time, burst time, and priority for process " << pid[i] << ": ";
        cin >> at[i] >> bt[i] >> priority[i];
    }

    sortByArrival(pid, at, bt, priority, flag, n);
    prioritySchedule(pid, at, bt, priority, ct, tat, wt, flag, n);
    printProcesses(pid, at, bt, priority, ct, tat, wt, n);

    return 0;
}