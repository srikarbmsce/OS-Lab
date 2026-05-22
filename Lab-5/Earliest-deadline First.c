#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int deadline;
    int waitingTime;
    int turnaroundTime;
    int completed;
};

int main() {
    int n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nEnter Burst Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);

        printf("Enter Deadline for P%d: ", p[i].pid);
        scanf("%d", &p[i].deadline);

        p[i].completed = 0;
    }

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].deadline > p[j].deadline) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    for(i = 0; i < n; i++) {
        p[i].waitingTime = currentTime;
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;

        currentTime += p[i].burstTime;

        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
    }

    printf("\nEDF Scheduling Result:\n");
    printf("---------------------------------------------------\n");
    printf("PID\tBurst\tDeadline\tWaiting\tTurnaround\n");
    printf("---------------------------------------------------\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid,
               p[i].burstTime,
               p[i].deadline,
               p[i].waitingTime,
               p[i].turnaroundTime);
    }

    printf("---------------------------------------------------\n");

    printf("Average Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
