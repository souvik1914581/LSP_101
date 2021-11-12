#include <stdlib.h>
#include <stdio.h>
int g_gVar1;
int g_gVar2;
int g_gVar3 = 5;
int main()
{
	int l_var1 = -1;
	static int l_StaticVar = 5;
	static double l_Temp = 5.0;
	char *ptr = NULL;
	printf("Before malloc\n");
	getchar();	
	ptr = (char*)malloc(32 * sizeof(char));
	if(ptr == NULL)
	{
		perror("malloc\n");
		exit(EXIT_FAILURE);
	}
	printf("After malloc\n");
	getchar();
	free(ptr);
	printf("After free\n");
	getchar();
	return 0;
}
