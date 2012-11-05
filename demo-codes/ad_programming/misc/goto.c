#include <stdio.h>



int main(void)
{
	int a, b;

	a = 3;
	b = 5;

	goto L2;
L1:
	add(a, b);

	return 0;
}

int add(int a, int b)
{
	int c;
L2:
	c = a+b;
	goto L1;
}
