#ifndef LIB_FILE_COPY_H
#define LIB_FILE_COPY_H

/*ERRORS*/
#define INVALID_FD_ERROR	-1
#define INVALID_BUF_SIZE	-2
#define READ_FAILURE		-3
#define WRITE_FAILURE		-4
#define INPUT_OPEN_FAILURE	-5
#define OUTPUT_OPEN_FAILURE	-6
#define MEM_ALLOC_ERROR		-7
#define INVALID_ERRNUM_BUF	-8
#define UNDEFINED_ERROR		-30
#define SUCCESS			0

int fileCopy(int inFd,int outFd,int bufSize,int *errNum);

#endif
