#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
int main(int argc,char **argv)
{
	if(argc < 3)
	{
		printf("n value not given\n");
		exit(EXIT_FAILURE);
	}
	char *endptr = NULL;
	long int n = -1;
	int retVal = -1;
	errno = 0;
	n = strtol(argv[1],&endptr,10);
	if((errno == ERANGE && (n == LONG_MAX || n == LONG_MIN))
			||(errno != 0 && n == 0)){
		perror("strtol");
		exit(EXIT_FAILURE);
	}

	printf("n = %ld\n",n);

	retVal = fork();
	if(retVal == -1)
	{
		perror("fork\n");
		exit(EXIT_FAILURE);
	}
	if(retVal > 0)
	{
		/*parent process*/	
		printf("Child PID = %d\n",retVal);
		int wStatus = -1;
		retVal = wait(&wStatus);
		if(WIFEXITED(wStatus))
		{
			printf("Child exited with status %d\n",WEXITSTATUS(wStatus));
		}

	}
	else if(retVal == 0)
	{
		/*child process*/
		switch(argv[2][0])
		{
			case '2':
				exit(n);
				break;
			case '3':
				return(n);
				break;
			default:
				printf("No exit or return in child\n");
		}	
	}
	
	return 0;
}

