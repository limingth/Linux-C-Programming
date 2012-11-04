#include <stdio.h>
#include <stdlib.h>

int how_many_1(int n)
{
    unsigned int i;
	int result = 0;
	
	for(i = 0; i < sizeof(int) * 8; i++)
	{
		if((n >> i) & 0x01)
			result++;
	}
	return result;
}

int main(int argc, char *argv[])
{
	int n;
	
    printf("please input a number:");
	scanf("%d", &n);
	
    printf("%d '1' in %d\n", how_many_1(n), n);
    
	return 0;
}