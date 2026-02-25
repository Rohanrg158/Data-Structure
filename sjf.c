#include <stdio.h>
int main() {
    int n, i, j;
    int burst[20], process[20];
    int waiting[20], turnaround[20];
    int total_wait = 0, total_tat = 0;
    int temp;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &burst[i]);
        process[i] = i + 1;
    }
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(burst[i] > burst[j]) {
                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
    waiting[0] = 0;
    for(i = 1; i<n; i++){
    	waiting[0] = 0;
    	for(j = 0; j < i; j++) {
            waiting[i] += burst[j];
        }
        total_wait += waiting[i];
    }
    for(i = 0; i < n; i++) {
        turnaround[i] = burst[i] + waiting[i];
        total_tat += turnaround[i];
    }
    printf("\nPID\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n",
               process[i], burst[i], waiting[i], turnaround[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wait/n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);

    return 0;
}
