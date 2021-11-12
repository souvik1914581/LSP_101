#include "libFileCopy.h"
int main()
{
	int retVal = -1;
	int errNum = -1;
	retVal = fileCopy(1,2,64,&errNum);
	return 0;
}
