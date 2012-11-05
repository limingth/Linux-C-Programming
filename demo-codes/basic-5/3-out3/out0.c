#include <stdio.h>

#define ALL_NUM		6
#define COUNT_NUM	3
#define OUT_NUM		2

/* people id array such as (1,2,3,4,5,6) */
int people[ALL_NUM];

void init(void)
{
	int i;

	/* init id as 1,2,3,4,5,6 */
	for (i = 0; i < ALL_NUM; i++)
		people[i] = i + 1;

	return;
}


void print(void)
{
	int i;

	for (i = 0; i < ALL_NUM; i++)
		printf("%d ", people[i]);

	printf("\n");

	return;
}

int main(void)
{
	int left;	/* left people number */
	int pos;	/* which pos */
	int step;	/* which step */

	int counter = 0;

	left = ALL_NUM;
	pos = 0;
	step = 0;

	init();

	/* if there is still people in queue */
	while (left > 0)
	{
		/* pos++?  step++?   left--? */
		if (people[pos] > 0)
			step++;

		if (step == OUT_NUM && people[pos] != 0)
		{
			printf("%d out \n", people[pos]);
			people[pos] = 0;
			left--;
		}

#if 1
		printf("counter=%d ", counter++);
		printf("(pos=%d, step=%d, left=%d) : ", pos, step, left);
		print();
		getchar();
#endif

		//pos = ++pos % ALL_NUM;
		pos++;
		if (pos == ALL_NUM)
			pos = 0;

		//step = step % COUNT_NUM;
		if (step == COUNT_NUM)
			step = 0;

	}

	return 0;
}
