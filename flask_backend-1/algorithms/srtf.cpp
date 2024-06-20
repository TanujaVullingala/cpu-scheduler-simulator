#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int n;
    input >> n;
    std::vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        input >> processes[i].pid >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    std::vector<int> waiting_time(n), turnaround_time(n), response_time(n, -1);
    int current_time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, min_remaining_time = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                idx = i;
            }
        }

        if (idx != -1) {
            if (response_time[idx] == -1) response_time[idx] = current_time - processes[idx].arrival_time;
            current_time++;
            processes[idx].remaining_time--;
            if (processes[idx].remaining_time == 0) {
                completed++;
                waiting_time[idx] = current_time - processes[idx].arrival_time - processes[idx].burst_time;
                turnaround_time[idx] = current_time - processes[idx].arrival_time;
            }
        } else {
            current_time++;
        }
    }

    double avg_waiting_time = 0, avg_turnaround_time = 0, avg_response_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
        avg_response_time += response_time[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    avg_response_time /= n;

    output << avg_waiting_time << std::endl;
    output << avg_turnaround_time << std::endl;
    output << avg_response_time << std::endl;

    return 0;
}
