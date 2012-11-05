#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void func(void)
{
	unsigned long long a = 100000000;

	while (a--);
}

void testTime(struct timeval *priv, struct timeval *next)
{
	long long sec, usec, consume;
	sec = next->tv_sec - priv->tv_sec;
	usec = next->tv_usec - priv->tv_usec;
	if (sec) {
		consume = sec * 1000000 + usec;
	} else {
		consume =usec;
	}

	printf("Consume time = %lld\n", consume);
}

int main(void)
{
	int ret;
	struct timeval priv, next;

	gettimeofday(&priv, NULL);
	func();
	gettimeofday(&next, NULL);

	testTime(&priv, &next);		
	return 0;		
}
