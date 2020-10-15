#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<assert.h>
#define MIN_PID 100
#define MAX_PID 1000
pthread_mutex_t Lock;
struct process 
           {
		int pid, isAllocated;
	            }obj[MAX_PID-MIN_PID];
	
	int allocate_map() 
   {
		int i=MIN_PID;
		while(i<=MAX_PID)
           {
			obj[i-MIN_PID].pid=i;
			obj[i-MIN_PID].isAllocated=0;
			i++;
		}
		return 1;
	}
	
	int allocate_pid()
   {
		int i=0;
		while(i<MAX_PID)
        {
			if (obj[i]. isAllocated==0) 
                       {
				pthread_mutex_lock(&Lock);
				obj[i]. isAllocated=1;
				pthread_mutex_unlock(&Lock);
				return obj[i].pid;
			}
			i++;
		}
		return -1;
	}
	
	void release_pid(int pid) 
{
		int i=0;
		while(i<MAX_PID) 
          {
			if(obj[i]. pid==pid) 
                       {
				int res=pthread_mutex_lock(&Lock);
                                    if(res==0)
                                   {
                                    printf("Aborting the process as res==0");
                                    } 
            				assert(res==0);
				obj[i]. isAllocated=0;
				res=pthread_mutex_unlock(&Lock);
				break;
			}
			i++;
		}
	}
	
	void* Func(void *args) 
{
		int pid=allocate_pid();
		printf("New process created: %d\n",pid);
		int time=(rand()+20)%(40+1);
		release_pid(pid);
		printf("Process destroyed with pid: %d\n",pid);
	}
	
	
	void createProcess() 
{
		int i=0,n;
            printf("How many threads");
            scanf("%d",&n);
		pthread_t threadPid[n];
		if(pthread_mutex_init(&Lock,NULL)!=0)
			printf("Mutex init.");
		while(i<n) 
           {
			pthread_create(&threadPid[i],NULL,Func,NULL);
			i++;
		}
	
		i=0;
		while(i<n) 
           {
			pthread_join(threadPid[i],NULL);
			i++;
		}	
	
	
                }			      
    int main() 
	{
 	if(allocate_map()) 
           {
		srand(time(0));
		createProcess();
		}
		return 0;
	}
	
