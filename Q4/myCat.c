#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "libFileCopy.h"
#include <unistd.h>

typedef enum APPMODE{
	APPMODE_UNDEF = -1,
	APPMODE_ECHO,
	APPMODE_CAT
}APPMODE;

int main(int argc,char **argv)
{
	int appMode = APPMODE_UNDEF;
	int sourceFd = 0;	/*STDIN as default sourceFd*/	
	int errNum = -1;	
	int retVal = -1;

	if(argc < 2)
	{
		appMode = APPMODE_ECHO;
	}
	else
	{
		appMode = APPMODE_CAT;
		
	}

	if(appMode == APPMODE_CAT)
	{
		/*open file*/
		sourceFd = open(argv[1],O_RDONLY | O_NONBLOCK);
		if(sourceFd == -1)
		{
			printf("Failed to open '%s' with error %d\n",argv[1],errno);
			exit(EXIT_FAILURE);
		}
	}
	
	retVal = fileCopy(sourceFd,1,64,&errNum);
	if(retVal != 0)
	{
		printf("fileCopy failed with error %d\n",errNum);
		exit(EXIT_FAILURE);
	}	

	if(appMode == APPMODE_CAT)
	{
		close(sourceFd);
	}	
	return 0;
}
