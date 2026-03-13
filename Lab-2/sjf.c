#include <stdio.h>

struct Process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int completed;
};

void sjf_nonpre(struct Process p[], int n){
    int completed = 0, current_time = 0;
    float avgwt = 0, avgtat = 0;

    while(completed < n){
        int idx = -1;
        int min_bt = 9999;

        for(int i = 0; i < n; i++){
            if(p[i].at <= current_time && p[i].completed == 0){
                if(p[i].bt < min_bt){
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if(idx != -1){
            p[idx].ct = current_time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            current_time = p[idx].ct;
            p[idx].completed = 1;
            completed++;

            avgwt += p[idx].wt;
            avgtat += p[idx].tat;
        }
        else{
            current_time++;
        }
    }

    avgwt /= n;
    avgtat /= n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", avgwt);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat);
}


void sjf_pre(struct Process p[], int n){
    int completed = 0, time = 0;
    float avgwt = 0, avgtat = 0;

    while(completed < n){
        int idx = -1;
        int min_rt = 9999;

        for(int i = 0; i < n; i++){
            if(p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt){
                min_rt = p[i].rt;
                idx = i;
            }
        }

        if(idx != -1){
            p[idx].rt--;
            time++;

            if(p[idx].rt == 0){
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                avgwt += p[idx].wt;
                avgtat += p[idx].tat;
            }
        }
        else{
            time++;
        }
    }

    avgwt /= n;
    avgtat /= n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", avgwt);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat);
}


int main(){
    int n;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct Process p[n];

    for(int i = 0; i < n; i++){
        p[i].pid = i + 1;

        printf("Enter Arrival time of Process %d: ", p[i].pid);
        scanf("%d",&p[i].at);

        printf("Enter Burst time of Process %d: ", p[i].pid);
        scanf("%d",&p[i].bt);

        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    int choice;

    printf("\nCPU Scheduling Menu\n");
    printf("1. SJF Non-Preemptive\n");
    printf("2. SJF Preemptive\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            sjf_nonpre(p,n);
            break;

        case 2:
            sjf_pre(p,n);
            break;

        default:
            printf("Invalid Choice\n");
    }

    return 0;
}
