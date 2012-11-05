#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t cur = time(NULL);
	printf("%s\n", ctime(&cur));
	return 0;
}
