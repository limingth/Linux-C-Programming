#include <stdio.h>

int get_bit(int num, int pos)
{
	if (num & (1<<pos))
		return 1;

	return 0;
}

int set_bit(int num, int pos, int value)
{
	if (value)
		return (num | (1<<pos));

	return (num & ~(1<<pos));
}

int count_bit(int num)
{
	int sum = 0;
	int i = 0;

	for (i = 0; i < 32; i++)
		sum += get_bit(num, i);

	return sum;
}

int main(void)
{
	printf("hello, demo bit \n");

	printf("v = %d\n", get_bit(0xe, 0));
	printf("v = %d\n", get_bit(0xe, 1));
	printf("v = %d\n", get_bit(0xe, 4));

	printf("v = %d\n", set_bit(0xe, 0, 1));
	printf("v = %d\n", set_bit(0xe, 3, 0));

	printf("v = %d\n", count_bit(0xffffffff));
	return 0;
}
