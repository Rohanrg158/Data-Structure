#include <stdio.h>
struct Process {
    int pid;
    int arrival;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turn_around_time;
    int remaining_time; 
    int priority;
};
void FCFS(int n, struct Process p[]) {
    int time = 0;
    float total_waiting = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival) 
            time = p[i].arrival;
        time += p[i].burst_time;
        p[i].completion_time = time;
        p[i].turn_around_time = p[i].completion_time - p[i].arrival;
        p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
        total_waiting += p[i].waiting_time;
    }
    float avg_waiting = total_waiting / n;
    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst_time, p[i].completion_time,
               p[i].waiting_time, p[i].turn_around_time);
    }
    printf("\nAverage Waiting Time = %.2f\n", avg_waiting);
}
void SJF(int n, struct Process p[]) {
    int total_wait = 0, total_tat = 0;
    struct Process temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].burst_time > p[j].burst_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    p[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
        total_wait += p[i].waiting_time;
    }
    for (int i = 0; i < n; i++) {
        p[i].turn_around_time = p[i].burst_time + p[i].waiting_time;
        total_tat += p[i].turn_around_time;
    }
    printf("\nPID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turn_around_time);
    }
    printf("\nAverage Waiting Time = %.2f", (float)total_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}
void PriorityScheduling(int n, struct Process p[]) {
    struct Process temp;
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    p[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
    }
    for (int i = 0; i < n; i++) {
        p[i].turn_around_time = p[i].burst_time + p[i].waiting_time;
    }
    printf("\nPID\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].burst_time, p[i].priority, p[i].waiting_time, p[i].turn_around_time);
        total_wt += p[i].waiting_time;
        total_tat += p[i].turn_around_time;
    }
    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}
void roundRobin(int n, struct Process p[], int quantum) {
    int time = 0;
    int remaining_processes = n;
    int i;
    for (i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
    }
    while (remaining_processes > 0) {
        for (i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                if (p[i].remaining_time > quantum) {
                    time += quantum;
                    p[i].remaining_time -= quantum;
                    printf("P%d executed for %d units, remaining time: %d\n", p[i].pid, quantum, p[i].remaining_time);
                } else {
                    time += p[i].remaining_time;
                    printf("P%d executed for %d units and completed\n", p[i].pid, p[i].remaining_time);
                    p[i].remaining_time = 0;
                    remaining_processes--;
                }
            }
        }
    }
    printf("All processes completed in %d units of time.\n", time);
}
int main() {
    int n, choice, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter burst time for Process P%d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Enter priority for Process P%d: ", i + 1);
        scanf("%d", &p[i].priority);
    }
    printf("\nChoose the scheduling algorithm:\n");
    printf("1. FCFS (First Come First Serve)\n2. SJF (Shortest Job First)\n3. Priority Scheduling\n4. Round Robin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            FCFS(n, p);
            break;
        case 2:
            SJF(n, p);
            break;
        case 3:
            PriorityScheduling(n, p);
            break;
        case 4:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &quantum);
            roundRobin(n, p, quantum);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
    return 0;
}
