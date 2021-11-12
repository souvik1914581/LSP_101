#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

void sigHandlerFunc(int signum)
{
	switch(signum)
	{
		case SIGINT:
			printf("Caught SIGINT\n");
			break;
		case SIGTERM:
			printf("Caught SIGTERM\n");
			break;
		case SIGQUIT:
			printf("Caught SIGQUIT\n");
			break;
		default:
			printf("Caught unhandled signal\n");
	}
}

int main()
{
	struct sigaction newAct;
	memset(&newAct,0,sizeof(struct sigaction));
	newAct.sa_handler = sigHandlerFunc;
	int retVal = -1;
	for(int signo = 1 ; signo <= 31 ; ++signo)
	{
		if(signo == SIGINT || signo == SIGTERM || signo == SIGQUIT)
		{
			retVal = sigaction(signo,&newAct,NULL);	
			if(-1 == retVal)
			{
				perror("sigaction\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	/*Infinite loop*/
	while(1);
	return 0;
}	

