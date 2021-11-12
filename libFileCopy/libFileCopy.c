#include "libFileCopy.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int fileCopy(int inFd,int outFd,int bufSize,int *errNum)
{
	int bytesRead = 0;
	int bytesWrite = 0;
	int retVal = SUCCESS;		
	/*Validate errNum ptr*/
	if(errNum == NULL)
	{
		return INVALID_ERRNUM_BUF;	
	}	
	*errNum = UNDEFINED_ERROR;

	/*validate the fds*/
	if(inFd < 0 || outFd < 0)
	{
		return INVALID_FD_ERROR;
	}

	/*validate the bufSize*/
	if(bufSize < 0 || bufSize > __INT_MAX__)
	{
		return INVALID_BUF_SIZE;
	}

	char *copyBuff = NULL; 
	copyBuff = (char*)malloc(bufSize * sizeof(char));
	if(copyBuff == NULL)
	{
		*errNum = errno;	
		return MEM_ALLOC_ERROR;
	}
	
	/*copy loop: read bufSize bytes from input file and write it to output file*/
		do{
			bytesRead = read(inFd,copyBuff,bufSize);
			if(bytesRead == -1)
			{
				retVal = READ_FAILURE;
				*errNum = errno;
				break;
			}	

			/*copy the read bytes to the output file*/
			bytesWrite = write(outFd,copyBuff,bytesRead);
			if(bytesWrite < 0)
			{
				retVal = WRITE_FAILURE;
				*errNum = errno;
				break;
			}
			/*reset the buffer*/
			memset(copyBuff,0,bufSize);

		}while(bytesRead > 0);

		/*free the buffer*/
		free(copyBuff);
		
		return retVal;			
}
