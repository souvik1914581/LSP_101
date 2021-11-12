#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc,char **argv)
{
	if(argc < 2)
	{
		printf("File not specified!\n");
		exit(EXIT_FAILURE);
	}
	int fd1 = -1;
	int fd2 = -1;
	fd1 = open(argv[1],O_RDONLY | O_NONBLOCK);
	if(fd1 == -1)
	{
		printf("Failed to open %s with error %d\n",argv[1],errno);
		exit(EXIT_FAILURE);
	}
	fd2 = dup(fd1);
	if(fd2 == -1)
	{
		printf("dup failed with error %d\n",errno);
		exit(EXIT_FAILURE);
	}

	char *buf = NULL;
	buf = (char*)malloc(64 * sizeof(char));
	if(buf == NULL)
	{
		printf("malloc failed with error %d\n",errno);
		exit(EXIT_FAILURE);
	}
	
	read(fd1,buf,100);
	getchar();
	read(fd2,buf,10);
	getchar();
	read(fd1,buf,10);
	getchar();
	read(fd2,buf,100);
	getchar();

	free(buf);
	close(fd1);
	close(fd2);
	
	return 0;
}
