#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

void sortProcesses(vector<string>& pid, vector<int>& at, vector<int>& bt, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }
}

void calculateTimes(vector<int>& at, vector<int>& bt, vector<int>& ct, vector<int>& tat, vector<int>& wt, int n) {
    int curr = 0;
    for (int i = 0; i < n; i++) {
        if (curr < at[i]) {
            curr = at[i];
        }
        ct[i] = curr + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        curr = ct[i];
    }
}

void printProcesses(const vector<string>& pid, const vector<int>& at, const vector<int>& bt, int n) {
    cout << "Process\tArrival Time\tBurst Time\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t\t" << bt[i] << "\n";
    }
}

void printResults(const vector<string>& pid, const vector<int>& at, const vector<int>& bt, const vector<int>& ct, const vector<int>& tat, const vector<int>& wt, int n) {
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t"
             << ct[i] << "\t\t" << tat[i] << "\t\t" << wt[i] << "\n";
    }
}

void printGanttChart(const vector<string>& pid, const vector<int>& at, const vector<int>& bt, const vector<int>& ct, int n) {
    int curr = 0;
    float sum_tat = 0, sum_wt = 0;
    vector<int> tat(n), wt(n);
    
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        sum_tat += tat[i];
        sum_wt += wt[i];
    }

    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < n; i++) {
        if (curr < at[i]) {
            for (int j = curr; j < at[i]; j++) cout << "--";
        }
        for (int j = 0; j < bt[i]; j++) cout << "--";
        cout << " ";
        curr = ct[i];
    }

    cout << "\n|";
    curr = 0;
    for (int i = 0; i < n; i++) {
        if (curr < at[i]) {
            cout << " IDLE |";
            curr = at[i];
        }
        for (int j = 0; j < bt[i] - 1; j++) cout << " ";
        cout << pid[i];
        for (int j = 0; j < bt[i] - 1; j++) cout << " ";
        cout << "|";
        curr = ct[i];
    }
    cout << "\n ";
    curr = 0;
    for (int i = 0; i < n; i++) {
        if (curr < at[i]) {
            for (int j = curr; j < at[i]; j++) cout << "--";
        }
        for (int j = 0; j < bt[i]; j++) cout << "--";
        cout << " ";
        curr = ct[i];
    }
    cout << "\n";

    curr = 0;
    cout << "0";
    for (int i = 0; i < n; i++) {
        if (curr < at[i]) {
            for (int j = curr; j < at[i]; j++) cout << " ";
            cout << at[i];
            curr = at[i];
        }
        for (int j = 0; j < bt[i]; j++) cout << " ";
        cout << ct[i];
        curr = ct[i];
    }
    cout << "\n";

    cout << fixed << setprecision(2);
    cout << "The average turn around time : " << (sum_tat) / n << "\n";
    cout << "The average waiting time : " << (sum_wt) / n << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<string> pid(n);
    vector<int> at(n), bt(n), ct(n), tat(n), wt(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the process ID of Process " << i + 1 << ": ";
        cin >> pid[i];
        cout << "Enter the arrival time and burst time for process " << pid[i] << ": ";
        cin >> at[i] >> bt[i];
        cout << "\n";
    }

    cout << "Processes before sorting:\n";
    printProcesses(pid, at, bt, n);

    sortProcesses(pid, at, bt, n);

    cout << "\nProcesses sorted by arrival time:\n";
    printProcesses(pid, at, bt, n);

    calculateTimes(at, bt, ct, tat, wt, n);

    printGanttChart(pid, at, bt, ct, n);

    cout << "\nProcesses with calculated times:\n";
    printResults(pid, at, bt, ct, tat, wt, n);

    return 0;
}
