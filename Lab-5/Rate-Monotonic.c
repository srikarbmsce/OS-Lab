#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    int period;
    int execution_time;
    int remaining_time;
    int next_release;
    int next_deadline;
    int deadline_misses;
} Task;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int choose_task(Task tasks[], int n) {
    int best = -1;
    for (int i = 0; i < n; i++) {
        if (tasks[i].remaining_time > 0) {
            if (best == -1 || tasks[i].period < tasks[best].period ||
               (tasks[i].period == tasks[best].period && tasks[i].id < tasks[best].id)) {
                best = i;
            }
        }
    }
    return best;
}

int main(void) {
    int n;
    printf("Rate Monotonic Scheduling\n");
    printf("Enter number of periodic tasks: ");
    scanf("%d", &n);
    Task *tasks = malloc(n * sizeof(Task));

    double utilization = 0.0;
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d period: ", tasks[i].id);
        scanf("%d", &tasks[i].period);
        printf("Task %d execution time: ", tasks[i].id);
        scanf("%d", &tasks[i].execution_time);
        tasks[i].remaining_time = 0;
        tasks[i].next_release = 0;
        tasks[i].next_deadline = tasks[i].period;
        tasks[i].deadline_misses = 0;
        utilization += (double)tasks[i].execution_time / tasks[i].period;
    }

    int hyperperiod = tasks[0].period;
    for (int i = 1; i < n; i++) {
        hyperperiod = lcm(hyperperiod, tasks[i].period);
    }

    printf("\nSchedule simulation for hyperperiod = %d time units\n", hyperperiod);
    printf("Total CPU utilization = %.3f\n", utilization);
    if (utilization > n * (pow(2.0, 1.0 / n) - 1.0)) {
        printf("Utilization exceeds the RM sufficient schedulability bound. Program will finish.\n");
        free(tasks);
        return 0;
    }
    printf("\n");

    int *schedule = malloc(hyperperiod * sizeof(int));

    for (int time = 0; time < hyperperiod; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release) {
                if (tasks[i].remaining_time > 0) {
                    tasks[i].deadline_misses++;
                }
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_release += tasks[i].period;
                tasks[i].next_deadline = time + tasks[i].period;
            }
        }

        int selected = choose_task(tasks, n);
        if (selected != -1) {
            schedule[time] = tasks[selected].id;
            tasks[selected].remaining_time--;
        } else {
            schedule[time] = 0;
        }

        for (int i = 0; i < n; i++) {
            if (time + 1 == tasks[i].next_deadline) {
                if (tasks[i].remaining_time > 0) {
                    tasks[i].deadline_misses++;
                    tasks[i].remaining_time = 0;
                }
            }
        }
    }

    printf("Schedule (time ranges):\n");
    printf("From\tTo\tTask\n");
    int start = 0;
    int currentTask = schedule[0];

    for (int time = 1; time <= hyperperiod; time++) {
        int taskAtTime = (time < hyperperiod) ? schedule[time] : -1;
        if (taskAtTime != currentTask) {
            const char *taskName = (currentTask == 0) ? "IDLE" : "T";
            if (currentTask == 0) {
                printf("%4d\t%2d\t%s\n", start, time, taskName);
            } else {
                printf("%4d\t%2d\tT%d\n", start, time, currentTask);
            }
            start = time;
            currentTask = taskAtTime;
        }
    }
    printf("\nTask summary:\n");
    printf("Task\tPeriod\tExec\tMisses\n");
    for (int i = 0; i < n; i++) {
        printf("T%d\t%d\t%d\t%d\n", tasks[i].id, tasks[i].period, tasks[i].execution_time, tasks[i].deadline_misses);
    }

    free(tasks);
    free(schedule);
    return 0;
}
