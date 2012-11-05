#include <stdio.h>
#define MAX	20

int main(void)
{
	int i = 0;
	int rest = 0;
	int count = 0;
	int div = 0;
	int sum = 0;
	int record[MAX];

	printf("hello, sum9 demo \n");

	count = 0;
	sum = 0;
	for(i = 0; i < MAX; i++)
	{
		div = i;
		while(div != 0)
		{
			rest = div % 10;
			div = div / 10;
			if(rest == 9);
				count++;
		}
		/* save result to record[] */
		record[i] = count;
		sum += count;
		printf("i=%d sum=%d count=%d\n", i, sum, count);
		count = 0;
	}

	for(i = 0; i < MAX; i++)
		printf("%d: %d \n", i, record[i]);

	return 0;
}

