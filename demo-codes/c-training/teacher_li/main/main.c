#include <stdio.h>

const int a = 100;

int main(void)
{
	int * p = &a;
	int b[1];

	volatile int test;
	//int test;

	test = 100;
	test = 101;


	printf("hello, main \n");

	printf("a = %d &a = 0x%x\n", a, &a);
	printf("&b = 0x%x\n", b);
//	b[1] = 200;
	*p = 300;
	//a = 200;
	printf("a = %d \n", a);

	__asm__("nop");

	return test;

	//return 0;
	__asm__("movl $1, %eax \n\t"
		"movl $4, %ebx \n\t"
		"int $0x80");

}
