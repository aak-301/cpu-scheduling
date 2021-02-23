#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct process_detail{
int pid;
int arrival_time;
int cpu_burst_time;
int completion_time;
int idle_time;
int turn_around_time;
int response_time;
};
int main(int argc, char *argv[])
{
	//0. process id
	//1. arrival time
	//2. burst time
	
	float cpu_utilisation;
	float total_idle_time=0;
	float total_completion_time=0;
	int t=(argc-1)/3;
	struct process_detail p[t][7];
	int i,j,c=1;
	for(i=0;i<t;i++){
		int count=0;
		while(count<3){
			    if(count==0)
				p[i][count].pid =  atoi(argv[c]);
			    
		 	    else if(count==1)
		 			p[i][count].arrival_time =  atoi(argv[c]);
		 		
		 	    
		 	    else if(count==2)
		 		p[i][count].cpu_burst_time =  atoi(argv[c]);

			count+=1;
	 		c+=1;
	 	}
	}	
	
	// sorting the structure on the basis of arrival_time

	int temp_pid;
	int temp_arrival_time;
	int temp_cpu_burst_time;
	for(i=0;i<t-1;i++){
		for(j=0;j<t-1;j++){
			if(p[j][1].arrival_time > p[j+1][1].arrival_time){
				temp_pid=p[j][0].pid;
				temp_arrival_time=p[j][1].arrival_time;
				temp_cpu_burst_time=p[j][2].cpu_burst_time;
			
				p[j][0].pid = p[j+1][0].pid;
				p[j][1].arrival_time = p[j+1][1].arrival_time;
				p[j][2].cpu_burst_time = p[j+1][2].cpu_burst_time;
				
				p[j+1][0].pid = temp_pid;
				p[j+1][1].arrival_time = temp_arrival_time;
				p[j+1][2].cpu_burst_time = temp_cpu_burst_time;
		}
	}
}
		

	//3. completion time
	
	for(i=0;i<t;i++){
		if(i==0){
			p[i][3].completion_time = p[i][1].arrival_time + p[i][2].cpu_burst_time;
		}
		else if ((p[i][1].arrival_time - p[i-1][3].completion_time) < 0 ){
			p[i][3].completion_time = p[i-1][3].completion_time + p[i][2].cpu_burst_time;
		}
		else{
			p[i][3].completion_time = p[i][1].arrival_time + p[i][2].cpu_burst_time;		
		}
		
		total_completion_time+=p[i][3].completion_time;
	}
	
	//4. idle time

	for(i=0;i<t;i++){
		if(i==0){
			if(p[i][1].arrival_time != 0)
				p[i][4].idle_time = p[i][1].arrival_time - 0;
			else{
				p[i][4].idle_time = 0;
			}
		}
		else if(p[i][1].arrival_time - p[i-1][3].completion_time <= 0)
			p[i][4].idle_time = 0;
			
		else
			p[i][4].idle_time = p[i][1].arrival_time - p[i-1][3].completion_time;
			
		total_idle_time+=p[i][4].idle_time;
	}
	
	//5. Turn around time
	
	for(i=0;i<t;i++)
		p[i][5].turn_around_time = p[i][3].completion_time - p[i][1].arrival_time;
	
	//6. Response time
	
	for(i=0;i<t;i++)
		p[i][6].response_time = p[i][3].completion_time - p[i][1].arrival_time - p[i][2].cpu_burst_time;
		

	// utilization 
		cpu_utilisation = (total_completion_time - total_idle_time)/total_completion_time ;
		
		printf("\n\n");
		printf("pid \t AT \t BT \t CT \t IT \t TT \t RT");
	for (i=0;i<t;i++)
		printf("\n%d \t %d \t %d \t %d \t %d \t %d \t %d",p[i][0].pid,p[i][1].arrival_time,p[i][2].cpu_burst_time,p[i][3].completion_time,p[i][4].idle_time,p[i][5].turn_around_time,p[i][6].response_time);
	printf("\n\ncpu utilization is = %f %%", cpu_utilisation);
	
}
