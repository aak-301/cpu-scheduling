#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 


int min(int a, int b){
	if(a>b) return a;
	else return b;
}
int max(int a, int b){
	if(a>b) return a;
	else return b;
}
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

int main(int argc,char *argv[]) {

    int n,i;
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int is_completed[100] = {0};

    scanf("%d",&n);
    struct process p[n];
    for(i = 0; i < n; i++) {        
        scanf("%d",&p[i].arrival_time);
        scanf("%d",&p[i].burst_time);
        scanf("%d",&p[i].priority);
        p[i].pid = i+1;
        burst_remaining[i] = p[i].burst_time;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;
            
            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }  
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float) max_completion_time )*100;
    throughput = (float)n / (max_completion_time - min_arrival_time);

    printf("\n\n");

    printf("Pid\tAT\tBT\tPRI\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++) {
    	printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].priority,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time,p[i].response_time);
    }
    printf("\n\nCpu utilisation = %f",cpu_utilisation);


}
