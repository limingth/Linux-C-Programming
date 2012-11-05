#include <stdio.h>

#define ALL_NUM 	100
#define STEP_NUM	3
#define OUT_NUM		3

int people[ALL_NUM];

int main(void)
{
	short i = 0;
	int step = 0;
	int counter = 0;

	printf("hello, out demo \n");

	// init array people[ALL_NUM]
	for (i = 0; i < ALL_NUM; i++)
		people[i] = i + 1;	

	// out people number != ALL_NUM 
	i = 0;
	while (counter != ALL_NUM)
	{
		if (people[i] != 0)
			step++;	

		if (step == OUT_NUM && people[i] != 0)
		{
			counter++;
		//	if (counter == ALL_NUM)
			printf("%d: %d is out\n", counter, people[i]);
			people[i] = 0;
		}
		step = step % STEP_NUM;
		i = (i+1) % ALL_NUM;
	}

	return 0;
}
