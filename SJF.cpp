#include <iostream>
#include <algorithm> // for swap
#include <numeric>   // for accumulate
using namespace std;

int main()
{
    int burst_time[20], p[20], waiting_time[20], tat[20], n;
    float avg_waiting_time, avg_tat;

    cout << "Please enter the number of processes: ";
    cin >> n;

    cout << "\nEnter the Burst Time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "p" << i + 1 << ":";
        cin >> burst_time[i];
        p[i] = i + 1;
    }

    // Sorting burst times using std::sort
    for (int i = 0; i < n; i++)
    {
        int minIndex = min_element(burst_time + i, burst_time + n) - burst_time;
        swap(burst_time[i], burst_time[minIndex]);
        swap(p[i], p[minIndex]);
    }

    // Calculating waiting times
    waiting_time[0] = 0;
    partial_sum(burst_time, burst_time + n - 1, waiting_time + 1);

    // Calculating average waiting time
    avg_waiting_time = accumulate(waiting_time, waiting_time + n, 0.0) / n;

    // Calculating turnaround times and total turnaround time
    int total_tat = 0;
    for (int i = 0; i < n; i++)
    {
        tat[i] = burst_time[i] + waiting_time[i];
        total_tat += tat[i];
    }

    // Calculating average turnaround time
    avg_tat = static_cast<float>(total_tat) / n;

    // Outputting the results
    cout << "\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
    for (int i = 0; i < n; i++)
    {
        cout << "\np" << p[i] << "\t\t  " << burst_time[i] << "\t\t    " << waiting_time[i] << "\t\t\t" << tat[i];
    }

    cout << "\n\nThe average Waiting Time = " << avg_waiting_time;
    cout << "\nThe average Turnaround Time = " << avg_tat << "\n";

    return 0;
}