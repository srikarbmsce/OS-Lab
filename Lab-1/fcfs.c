#include<stdio.h>
struct process{
    int pid;
    int at;
    int bt;
}process[100];

int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    float awt = 0;
    float atat = 0;

    int ct[n];
    int tat[n];
    int wt[n];

    for(int i=0;i<n;i++){
        printf("Enter details of process %d\n",i+1);

        printf("Enter Arrival time: ");
        scanf("%d",&process[i].at);

        printf("Enter Burst time: ");
        scanf("%d",&process[i].bt);

        process[i].pid = i+1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            if(process[j].at>process[j+1].at){
                int tempat = process[j].at;
                int tempbt = process[j].bt;
                int temppid = process[j].pid;

                process[j].at = process[j+1].at;
                process[j].bt = process[j+1].bt;
                process[j].pid = process[j+1].pid;

                process[j+1].at = tempat;
                process[j+1].bt = tempbt;
                process[j+1].pid = temppid;
            }
        }
    }

    printf("Details of processes:\n");
    printf("pid\tat\tbt\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\n",process[i].pid,process[i].at,process[i].bt);
    }

    int current_time = 0;
    for(int i=0;i<n;i++){
        if(current_time<process[i].at){
            current_time = process[i].at;
        }
        ct[i] = current_time + process[i].bt;
        tat[i] = ct[i] - process[i].at;
        wt[i] = tat[i] - process[i].bt;

        current_time = ct[i];

        awt = awt + wt[i];
        atat = atat + tat[i];
    }

    awt = awt/n;
    atat = atat/n;

    printf("Results\n");
    printf("pid\tat\tbt\tct\twt\ttat\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",process[i].pid,process[i].at,process[i].bt,ct[i],wt[i],tat[i]);
    }
    printf("Average Waiting time: %f\n",awt);
    printf("Average Turnaround time: %f",atat);
    return 0;
}
