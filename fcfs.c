#include <stdio.h>
struct Process{
	int pid;
	int arrival; 
	int burst;
	int completion;
	int waiting;
	int turnaround;
};
int main(){
int n, time;
float total_waiting = 0;
printf("Enter number of processes: ");
scanf("%d", &n);
struct Process p[n]; 
for (int i = 0; i < n; i++) {
	printf("\nProcess %d\n", i + 1);
	p[i].pid = i + 1;
	printf("Arrival Time: ");
	scanf("%d", &p[i].arrival);
	printf("Burst Time: ");
	scanf("%d", &p[i].burst);
	}
for (int i = 0; i < n; i++) {
if (time < p[i].arrival)
	time = p[i].arrival;
	time += p[i].burst;
	p[i].completion = time;
	p[i].turnaround = p[i].completion - p[i].arrival;
	p[i].waiting = p[i].turnaround - p[i].burst;
	total_waiting += p[i].waiting;
	}
float avg_waiting = total_waiting / n;
printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
for (int i = 0; i < n; i++) {
	printf("%d\t%d\t%d\t%d\t%d\t%d\n",
	p[i].pid,
	p[i].arrival,
	p[i].burst,
	p[i].completion,
	p[i].waiting,
	p[i].turnaround);
	}
printf("\nAverage Waiting Time = %.2f\n", avg_waiting);
return 0;
}
