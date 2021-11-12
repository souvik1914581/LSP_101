#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc,char **argv)
{
	int sourceFd = -1;
	int retVal = -1;
	char *buf = NULL;
	if(argc < 2)
	{
		printf("No filename specified!\n");
		exit(EXIT_FAILURE);
	}	
	
	/*open file for reading*/
	sourceFd = open(argv[1],O_RDONLY | O_NONBLOCK);
	if(sourceFd == -1)
	{
		printf("Failed to open '%s',error : %d\n",argv[1],errno);
		exit(EXIT_FAILURE);
	}	
	/*duplicate the file fd to fd 0*/	
	retVal = dup2(sourceFd,0);
	if(retVal == -1)
	{
		printf("dup2 failed with error %d\n",errno);
		exit(EXIT_FAILURE);
	}
	printf("retVal = %d\n",retVal);
	
	buf = (char*)malloc(64 * sizeof(char));
	if(buf == NULL)
	{
		printf("malloc failure!\n");
		exit(EXIT_FAILURE);
	}
	buf[63] = '\0';
	
	/*read from stdin and write to stdout*/
	for(int i = 0; i < 5 ; ++i)
	{
		retVal = read(0,buf,sizeof(buf) - 1);
		if(retVal == -1)
		{
			printf("Read failed with error %d\n",errno);
			free(buf);
			exit(EXIT_FAILURE);
		}
		retVal = write(1,buf,sizeof(buf) - 1);
		if(retVal == -1)
		{
			printf("Write failed with error %d\n",errno);
			free(buf);
			exit(EXIT_FAILURE);
		}
		memset(buf,0,64);
	}
	getchar();
	free(buf);
	close(sourceFd);
	return 0;
}
