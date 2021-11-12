#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
int main(int argc,char **argv)
{
	if(argc < 2)
	{
		printf("n value not given\n");
		exit(EXIT_FAILURE);
	}
	char *endptr = NULL;
	long int n = -1;
	int retVal = -1;
	int *pids = NULL;
	int i = -1;
	int wStatus = -1;
	long int randVal = -1;
		
	/*zeroing the errno before using strtol*/
	errno = 0;
	n = strtol(argv[1],&endptr,10);
	if((errno == ERANGE && (n == LONG_MAX || n == LONG_MIN))
			||(errno != 0 && n == 0)){
		perror("strtol");
		exit(EXIT_FAILURE);
	}
	pids = (int*)calloc(n,sizeof(int));

	printf("num childs = %ld\n",n);
	for(i = 0 ; i < n ; ++i)
	{

		pids[i] = fork();
		if(pids[i] == -1)
		{
			perror("fork\n");
			exit(EXIT_FAILURE);
		}
		if(pids[i] > 0)
		{
			/*parent process*/	
			printf("Created Child %d: PID = %d\n",i+1,pids[i]);
			wStatus = -1;
			retVal =  waitpid(pids[i],&wStatus,WNOHANG);
			if(retVal == -1)
			{
				perror("waitpid \n");
			}
			if(retVal == 0)
			{
				//printf("Child %d yet to exit\n",pids[i]);
				continue;
			}
			if(retVal == pids[i])
			{
				if(WIFEXITED(wStatus))
				{
					printf("Child %d: PID %d exited with status %d\n",i+1,pids[i],WEXITSTATUS(wStatus));
					/*mark pid[i] = 0 to indicate that this child has exited already*/
					pids[i] = 0;
				}
			}

		}
		else if(pids[i] == 0)
		{
			/*child process*/
			struct timeval tv;
			memset(&tv,0,sizeof(struct timeval));
			retVal = gettimeofday(&tv,NULL);
			if(retVal == -1)
			{
				perror("gettimeofday\n");
			}
			srandom(tv.tv_usec);
			randVal = random() % 10;
			printf("Child %d sleeptime = %ld secs\n",i+1,randVal);
			sleep(randVal);
			exit(randVal);
			
		}
	}

	/*Do waitpid on the pids which are yet to exit*/
	for(int i = 0 ; i < n ; ++i)
	{
		if(pids[i] == 0)
			continue;
		retVal = waitpid(pids[i],&wStatus,0);
		if(retVal == -1)
		{
			perror("waitpid\n");
		}
		if(retVal == 0)
		{
			continue;
		}	
		if(retVal == pids[i])
		{
			if(WIFEXITED(wStatus))
				{
					printf("Child %d: PID %d exited with status %d\n",i+1,pids[i],WEXITSTATUS(wStatus));
				}
			else if(WIFSIGNALED(wStatus)){
				printf("Child %d: PID %d kiled by signal %d\n",i+1,pids[i],WTERMSIG(wStatus));
			}
		}
	}
	free(pids);	
	return 0;
}

