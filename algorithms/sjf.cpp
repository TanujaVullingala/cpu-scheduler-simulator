#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

bool compare(Process a, Process b) {
    return a.burst_time < b.burst_time;
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int n;
    input >> n;
    std::vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        input >> processes[i].pid >> processes[i].arrival_time >> processes[i].burst_time;
    }

    std::sort(processes.begin(), processes.end(), compare);

    std::vector<int> waiting_time(n), turnaround_time(n), response_time(n);
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        waiting_time[i] = current_time - processes[i].arrival_time;
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
        response_time[i] = waiting_time[i];
        current_time += processes[i].burst_time;
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
