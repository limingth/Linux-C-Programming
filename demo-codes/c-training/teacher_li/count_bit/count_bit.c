#include <stdio.h>

int count_bit(int num)
{
	int sum = 0;

	while(num)
	{
		sum++;
		num &= num-1;
	}

	return sum;
}

int main(void)
{
	unsigned char c = 0xFF;
	unsigned char t1, t2;
	unsigned char r1, r2, r3;

	int sum = 0;

	printf("hello, demo count_bit \n");
	printf("count %d = %d\n", 15, count_bit(0xff));

	t1 = c & 0x55;
	t2 = (c>>1) & 0x55;
	r1 = t1 + t2;
	// r1 = (c&0x55) + ((c>>1)&0x55);
	
	t1 = r1 & 0x33;
	t2 = (r1>>2) & 0x33;
	r2 = t1 + t2;
	// r2 = (r1&0x33) + ((r1>>2)&0x33);

	r3 = (r2 & 0x0f) + ((r2>>4) & 0x0f);
	printf("r3 = 0x%x \n", r3);

	return 44;
}
