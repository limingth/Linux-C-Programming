#include <stdio.h>

static int counter = 0;

int count_add(int num)
{
	printf("count_add called! \n");
	counter += num;
	return counter;
}

int count_add_one()
{
	printf("count_add called! \n");
	counter++;
	return counter;
}

int count_get_number()
{
	printf("count_get_number called! \n");
	return counter;
}

int count_zero()
{
	counter = 0;
	return 0;
}
