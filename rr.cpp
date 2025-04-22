#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sortByArrival(vector<string>& pid, vector<int>& at, vector<int>& bt, int n) {
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

void roundRobinSchedule(vector<string>& pid, vector<int>& at, vector<int>& bt, vector<int>& ct, vector<int>& tat, vector<int>& wt, int tq, int n) {
    int currTime = 0, cp = 0;
    vector<int> rt = bt;
    vector<int> order(2 * n), times(2 * n);
    int oi = 0;
    vector<int> queue(2 * n);
    int front = 0, rear = 0;
    vector<bool> vis(n, false);

    int idx = 0;
    while (idx < n && at[idx] <= currTime) {
        queue[rear++] = idx;
        vis[idx] = true;
        idx++;
    }

    cout << "\nGantt Chart:\n";
    cout << " --------------------------------------\n";
    cout << "|";

    while (cp < n) {
        if (front == rear) {
            cout << " I |";
            currTime = at[idx];
            times[oi++] = currTime;
            queue[rear++] = idx;
            vis[idx] = true;
            idx++;
        }
        int pidx = queue[front++];
        cout << " " << pid[pidx] << " |";

        if (rt[pidx] > tq) {
            currTime += tq;
            rt[pidx] -= tq;
        } else {
            currTime += rt[pidx];
            rt[pidx] = 0;
            ct[pidx] = currTime;
            tat[pidx] = ct[pidx] - at[pidx];
            wt[pidx] = tat[pidx] - bt[pidx];
            cp++;
        }
        order[oi] = pidx;
        times[oi++] = currTime;

        while (idx < n && at[idx] <= currTime) {
            queue[rear++] = idx;
            vis[idx] = true;
            idx++;
        }
        if (rt[pidx] > 0) {
            queue[rear++] = pidx;
        }
    }

    cout << "\n --------------------------------------\n";
    cout << "0";
    for (int i = 0; i < oi; i++) {
        cout << " " << times[i];
    }
    cout << "\n";
}

void printProcesses(const vector<string>& pid, const vector<int>& at, const vector<int>& bt, const vector<int>& ct, const vector<int>& tat, const vector<int>& wt, int n) {
    float sum_wt = 0, sum_tat = 0;
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << ct[i] << "\t\t" << tat[i] << "\t\t" << wt[i] << "\n";
        sum_wt += wt[i];
        sum_tat += tat[i];
    }
    cout << "\n\n";
    cout << "The average waiting time : " << (sum_wt / n) << endl;
    cout << "The average turn around time : " << (sum_tat / n) << endl;
}

int main() {
    int n, tq;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<string> pid(n);
    vector<int> at(n), bt(n), ct(n), tat(n), wt(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the process ID of Process " << i + 1 << ": ";
        cin >> pid[i];
        cout << "Enter the arrival time and burst time for process " << pid[i] << ": ";
        cin >> at[i] >> bt[i];
    }

    cout << "Enter the time quantum: ";
    cin >> tq;

    sortByArrival(pid, at, bt, n);
    roundRobinSchedule(pid, at, bt, ct, tat, wt, tq, n);
    printProcesses(pid, at, bt, ct, tat, wt, n);

    return 0;
}