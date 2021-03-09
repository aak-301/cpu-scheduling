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
  int k=0;
  struct process_details p[n];
  if(argc>=2)
  {
    for(int i = 1;i<argc;i=i+3)
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
    int i;
   int completed[n];
   int remaining[n];
   for(i=0;i<n;i++)
   {
      completed[i]=0;
      remaining[i]=p[i].cpu_burst_time;
   }
   int current_t=0,complete=0,prev=0,total_idle=0;
   
   while(complete!=n)
   {
      int in=-1;
      int mn=100000;
      for(i=0;i<n;i++)
      {
          if(p[i].arrival_time <= current_t && completed[i]==0)
          {
               if(remaining[i] < mn)
               {
                   mn = remaining[i];
                   in=i;
               }
               if(remaining[i] == mn)
               {
                   if(p[i].arrival_time < p[in].arrival_time)
                   {
                      mn = remaining[i];
                      in = i;
                   }
               }
          }
      }
      if(in!=-1)
      {
         if(remaining[in] == p[in].cpu_burst_time)
         {
             p[in].start_t = current_t;
             total_idle += p[in].start_t - prev;
         }
         remaining[in] -= 1;
         current_t++;
         prev = current_t;
         
         if(remaining[in]==0)
         {
              p[in].ct = current_t;
              p[in].tt = p[in].ct - p[in].arrival_time;
              p[in].rt = p[in].start_t - p[in].arrival_time;
              
              completed[in] = 1;
              complete++;
         }
      }
      else
      {
        current_t++;
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
