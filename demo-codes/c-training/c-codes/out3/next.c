#include <stdio.h>

#define ALL_NUM		100
#define STEP_NUM	3
#define OUT_NUM		3

int main(void)
{
	int next[ALL_NUM];	// save the next people's index 
	int i, prev_i;	
	int step = 0;		// 1, 2, 3
	int counter = 0;	// save the out people's sum number

	// init next[] array 
	for (i = 0; i < ALL_NUM; i++)
		next[i] = (i + 1) % ALL_NUM;

	// init i, prev_i
	i = 0;
	prev_i = ALL_NUM - 1;
	while (counter != ALL_NUM)
	{
		// step + 1
		step++;

		// judge if step = OUT
		if (step == OUT_NUM)
		{
			counter++;
		//	if (counter == ALL_NUM)
			printf("%d: %d is out\n", counter, i+1);

			// change next array
			next[prev_i] = next[i];
		}

		// change i to next i
		prev_i = i;
		i = next[i];

		// change step
		step = step % STEP_NUM;
	}

	return 0;
}
