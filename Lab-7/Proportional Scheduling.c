#include <stdio.h>

int main() {
    int n, i;
    int totalWeight = 0;
    int totalCPUTime;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int weight[n];
    float cpuShare[n];

    for(i = 0; i < n; i++) {
        printf("Enter weight for Process P%d: ", i + 1);
        scanf("%d", &weight[i]);

        totalWeight += weight[i];
    }

    printf("Enter total CPU time available: ");
    scanf("%d", &totalCPUTime);

    printf("\n--- Proportional Scheduling ---\n");
    printf("Process\tWeight\tCPU Share\tAllocated CPU Time\n");

    for(i = 0; i < n; i++) {
        cpuShare[i] = (float)weight[i] / totalWeight;

        printf("P%d\t%d\t%.2f\t\t%.2f units\n",
               i + 1,
               weight[i],
               cpuShare[i],
               cpuShare[i] * totalCPUTime);
    }

    return 0;
}
