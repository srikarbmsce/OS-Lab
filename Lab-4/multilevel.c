#include <stdio.h>

struct Process {
    int id;
    int at, bt;
    int remaining;
    int ct, tat, wt;
    int queue;
};

int main() {
    int n, i, time = 0, done;
    int quantum = 2;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess P%d\n", p[i].id);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Queue (1=System, 2=User): ");
        scanf("%d", &p[i].queue);

        p[i].remaining = p[i].bt;
        p[i].ct = 0;
    }

    do {
        done = 1;
        int executed = 0;

        for (i = 0; i < n; i++) {
            if (p[i].queue == 1 && p[i].remaining > 0 && p[i].at <= time) {
                done = 0;
                executed = 1;

                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    p[i].ct = time;
                }
            }
        }

        if (!executed)
            time++;

    } while (!done);

    for (i = 0; i < n; i++) {
        if (p[i].queue == 2) {
            if (time < p[i].at)
                time = p[i].at;

            time += p[i].bt;
            p[i].ct = time;
        }
    }

    float total_tat = 0, total_wt = 0;

    printf("\nProcess\tQueue\t\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;

        if (p[i].queue == 1)
            printf("P%d\tSystem\t\t", p[i].id);
        else
            printf("P%d\tUser\t", p[i].id);

        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f ms\n", total_tat / n);
    printf("Average Waiting Time = %.2f ms\n", total_wt / n);

    return 0;
}
