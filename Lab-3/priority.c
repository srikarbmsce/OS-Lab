#include <stdio.h>

struct Process {
    int pid, at, bt, pr;
    int ct, tat, wt;
    int rt;
    int completed;
};

void nonPreemptive(struct Process p[], int n) {
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    int INT_MAX = 10000;
    for (int i = 0; i < n; i++)
        p[i].completed = 0;

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].completed == 0) {
                if (p[i].pr < highest_priority) {
                    highest_priority = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
        }
        else {
            p[idx].ct = current_time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;

            p[idx].completed = 1;
            current_time = p[idx].ct;
            completed++;
        }
    }

    printf("\n--- Non-Preemptive Priority ---\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage WT = %.2f", total_wt / n);
    printf("\nAverage TAT = %.2f\n", total_tat / n);
}

void preemptive(struct Process p[], int n) {
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    int INT_MAX = 1000;
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].pr < highest_priority) {
                    highest_priority = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
        }
        else {
            p[idx].rt--;
            current_time++;

            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                total_wt += p[idx].wt;
                total_tat += p[idx].tat;
            }
        }
    }

    printf("\n--- Preemptive Priority ---\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage WT = %.2f", total_wt / n);
    printf("\nAverage TAT = %.2f\n", total_tat / n);
}

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Priority: ");
        scanf("%d", &p[i].pr);
    }

    printf("\nChoose Scheduling Type:\n");
    printf("1. Non-Preemptive Priority\n");
    printf("2. Preemptive Priority\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            nonPreemptive(p, n);
            break;

        case 2:
            preemptive(p, n);
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
