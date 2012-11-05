#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	time_t cur = time(NULL);

	struct tm *buf = localtime(&cur);

	printf("year:%d\n", buf->tm_year+1900);
	printf("mon:%d\n", buf->tm_mon+1);
	printf("wday:%d\n", buf->tm_wday+1);
	printf("day:%d\n", buf->tm_mday);
	printf("hour:%d\n", buf->tm_hour);
	printf("min:%d\n", buf->tm_min);
	printf("second:%d\n", buf->tm_sec);

	return 0;
}
