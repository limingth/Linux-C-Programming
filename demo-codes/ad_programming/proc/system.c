#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int ret = system("gbda");
	printf("ret=%d\n", ret);
	exit(0);
}
