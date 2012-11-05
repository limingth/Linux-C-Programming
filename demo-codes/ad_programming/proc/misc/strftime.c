#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t cur = time(NULL);

	struct tm *tm_cur = localtime(&cur);

	char buf[512];

	strftime(buf, 512, "%F  %r", tm_cur);

	printf("%s\n", buf);
	return 0;
}
