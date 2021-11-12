#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "libFileCopy.h"
#define FAILURE -1
#define SUCCESS 0
#define MAX_FILE_NAME_SIZE 128

void printUsage()
{
	printf("Usage:\ncopyFile [-f] <source> <destination>\n");
}


int main(int argc,char **argv)
{
	int retVal = FAILURE;	
	int opt = FAILURE;
	unsigned char overWriteFlag = 0;
	const char *optString = "f";
	char sourceFileName[MAX_FILE_NAME_SIZE] = {0};
	sourceFileName[MAX_FILE_NAME_SIZE - 1] = '\0';
	char destFileName[MAX_FILE_NAME_SIZE] = {0};
	destFileName[MAX_FILE_NAME_SIZE - 1] = '\0';

	int sourceFd = -1;
	int destFd = -1;
	int errNum = -1;	
	if(argc < 3)
	{
		printUsage();
		exit(EXIT_FAILURE);
	}
	
	while((opt = getopt(argc,argv,optString)) != -1)
	{
		switch(opt)
		{
			case 'f':
				overWriteFlag = 1;
				break;
			default:
				printUsage();
				exit(EXIT_FAILURE);
		}
	}

	switch(optind)
	{
		case 1:
			/*no -f option*/
			strncpy(sourceFileName,argv[1],sizeof(sourceFileName) - 1);	
			strncpy(destFileName,argv[2],sizeof(destFileName) - 1);
			
			break;
		case 2:
			/*-f option*/
			
			strncpy(sourceFileName,argv[2],sizeof(sourceFileName) - 1);	
			
			strncpy(destFileName,argv[3],sizeof(destFileName) - 1);
			break;
	}

		
			printf("Source file = '%s',Dest file = '%s',overWrite = '%u'\n",sourceFileName,destFileName,overWriteFlag);
	
	/*open the source file*/
	sourceFd = open(sourceFileName,O_RDONLY | O_NONBLOCK);
	if(sourceFd == -1)
	{
		printf("Failed to open '%s' with error '%s'\n",sourceFileName,strerror(errno));
		exit(EXIT_FAILURE);
	}

	/*check overWrite flag*/
	if(overWriteFlag)
	{
		/*create new dest file*/
		destFd = open(destFileName,O_CREAT | O_WRONLY | O_TRUNC,S_IRUSR | S_IWUSR|S_IRGRP | S_IWGRP);
		if(destFd == -1)
		{
			printf("Failed to create '%s' with error '%s'\n",destFileName,strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		destFd = open(destFileName,O_WRONLY | O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP);

		if(destFd == -1)
		{
			if(errno == EEXIST)
			{
				printf("Dest file already exists\n");
			}	
			printf("Failed to open '%s' with error '%s'\n",destFileName,strerror(errno));
			close(sourceFd);	
			exit(EXIT_FAILURE);
		}
	
	}			
	/*copy operation*/
	printf("sourceFd = %d,destFd = %d\n",sourceFd,destFd);
	retVal = fileCopy(sourceFd,destFd,64,&errNum);

	close(sourceFd);
	close(destFd);
	if(retVal != 0)
	{
		printf("Copy failed with errorNum %d\n",errNum);
		exit(EXIT_FAILURE);
	}
	printf("Copy successful!\n");
	return 0;
}
