#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
} Process;

void roundRobin(Process processes[], int n, int quantum) {
    int time = 0;
    int completed = 0;
    int *waiting_time = (int *)malloc(n * sizeof(int));
    int *turnaround_time = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        waiting_time[i] = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\n--- Round Robin Scheduling (Quantum = %d) ---\n", quantum);
    printf("Execution Order: ");

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                printf("P%d ", processes[i].pid);

                if (processes[i].remaining_time <= quantum) {
                    time += processes[i].remaining_time;
                    processes[i].completion_time = time;
                    turnaround_time[i] = processes[i].completion_time - processes[i].arrival_time;
                    waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    completed++;
                } else {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                }
            }
        }
    }

    printf("\n\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    float total_waiting = 0, total_turnaround = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time,
               waiting_time[i], turnaround_time[i]);
        total_waiting += waiting_time[i];
        total_turnaround += turnaround_time[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n\n", total_turnaround / n);

    free(waiting_time);
    free(turnaround_time);
}

int main() {
    int n = 4;
    Process processes[] = {
        {1, 0, 5, 0, 0},
        {2, 1, 4, 0, 0},
        {3, 2, 3, 0, 0},
        {4, 3, 6, 0, 0}
    };

    int quantums[] = {2, 4};

    printf("======= Round Robin CPU Scheduling =======\n");
    for(int i=0;i<n;i++) {
        printf("Processes: P%d(AT:%d,BT:%d) ", processes[i].pid, processes[i].arrival_time, processes[i].burst_time);
    }
    printf("\n");

    for (int i = 0; i < 2; i++) {
        Process temp[4];
        for (int j = 0; j < n; j++) temp[j] = processes[j];
        roundRobin(temp, n, quantums[i]);
    }

    return 0;
}
