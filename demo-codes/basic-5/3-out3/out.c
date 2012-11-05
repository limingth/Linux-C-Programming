#include <stdio.h>

#define ALL_NUM		1000
#define COUNT_NUM	5
#define OUT_NUM		3

/* people id array such as (1,2,3,4,5,6) */
//int people[ALL_NUM];
/* record people's next available position, -1 means OUT */
int next[ALL_NUM];

void init(void)
{
	int i;

	for (i = 0; i < ALL_NUM; i++)
	{
		/* init id as 1,2,3,4,5,6 */
//		people[i] = i + 1;

		/* init next position as 1,2,3,4,5,0 */
		next[i] = (i + 1) % ALL_NUM;
	}

	return;
}

void print(void)
{
	int i;

	for (i = 0; i < ALL_NUM; i++)
//		printf("%d(%d)  ", people[i], next[i]);
		printf("%d(%d)  ", i+1, next[i]);

	printf("\n");

	return;
}

int main(void)
{
	int left;			/* left people number */
	int pos, prev_pos, next_pos;	/* current pos, previous pos */
	int step;			/* which step */
	int tmp;

	int counter = 0;

	left = ALL_NUM;
	pos = 0;
	prev_pos = ALL_NUM - 1;
	step = 0;

	init();

	/* if there is still people in queue */
	while (left > 0)
	{
		/* pos++?  step++?   left--? */
		if (next[pos] != -1)
			step++;

		/* deal with the people to be out */
		if (step == OUT_NUM && next[pos] != -1)
		{
			printf("%d out \n", pos+1 ); 
			/* kick the people of this pos out */
			//people[pos] = 0;
			left--;

			/* set prev_pos'next = this'pos next */
			next[prev_pos] = next[pos];

			/* save current pos'next */
			next_pos = next[pos];

			/* kick the people of this pos out */
			next[pos] = -1;
		}

#if 0
		printf("counter=%d ", counter++);
		printf("(pos=%d, step=%d, left=%d) : ", pos, step, left);
		print();
		getchar();
#endif
		/* save current pos to prev_pos and get next pos */
		prev_pos = pos;
		if (next[pos] == -1)
			pos = next_pos;
		else
			pos = next[pos];

		//step = step % COUNT_NUM;
		if (step == COUNT_NUM)
			step = 0;

	}

	return 0;
}
