#include<stdio.h>
#include<stdlib.h>

struct process_details
{
   int pid;
   int arrival_time;
   int cpu_burst_time;
   int start_t;
   int ct;
   int tt;
   int rt;
   
};
int main(int argc,char *argv[])
{
  int in = argc - 1;
  int n = in/3;
  int k=0,i;
  struct process_details p[n];
  if(argc>=2)
  {
    for(i = 1;i<argc;i=i+3)
    {
       
       int a = atoi(argv[i]);
       int b = atoi(argv[i+1]);
       int c = atoi(argv[i+2]);
       p[k].pid = a;
       p[k].arrival_time = b;
       p[k].cpu_burst_time = c;
       k++;
    }
  }
   int completed[n];
   for(i=0;i<n;i++)
   {
      completed[i]=0;
   }
   int curr=0,complete=0,prev=0,total_idle=0;
   
   while(complete!=n)
   {
      int in=-1;
      int mn=100000;
      for(i=0;i<n;i++)
      {
          if(p[i].arrival_time <= curr && completed[i]==0)
          {
               if(p[i].cpu_burst_time < mn)
               {
                   mn = p[i].cpu_burst_time;
                   in=i;
               }
               if(p[i].cpu_burst_time == mn)
               {
                   if(p[i].arrival_time < p[in].arrival_time)
                   {
                      mn = p[i].cpu_burst_time;
                      in = i;
                   }
               }
          }
      }
      if(in!=-1)
      {
         p[in].start_t = curr;
         p[in].ct = p[in].start_t + p[in].cpu_burst_time;
         p[in].tt = p[in].ct - p[in].arrival_time;
         p[in].rt = p[in].start_t - p[in].arrival_time;
         
         total_idle += p[in].start_t - prev;
         
         completed[in] = 1;
         complete++;
         curr = p[in].ct;
         prev = curr;
      }
      else
      {
        curr++;
      }
   
   }
   
   int j;
  int flag=0;
   for(i=0;i<n-1;i++)
    {
      flag=0;
      for(j=0;j<n-i-1;j++)
      {
          if(p[j].ct > p[j+1].ct)
          {
             flag=1;
             struct process_details temp;
             temp = p[j];
             p[j] = p[j+1];
             p[j+1]=temp;
          }
      }
      if(flag==0)
        break;
    }
    printf("PID\tCT\tTT\tRT");
    for(i=0;i<n;i++)
    {
    printf("\n%d\t%d%d%d",p[i].pid,p[i].ct,p[i].tt,p[i].rt);
    }
    printf("\n");
    double cu = ((p[n-1].ct - total_idle)/(double)p[n-1].ct)*100;
    printf("cpu utilisation = %0.2lf\n",cu);
    
    return 0;
   
   
}
