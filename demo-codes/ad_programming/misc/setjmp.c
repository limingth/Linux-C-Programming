#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf buffer;
static int a = 9;
void func(void)
{
	printf("Enter func!\n");
	a++;
	longjmp(buffer, 101);
}

int main(void)
{
	int b = 9;
	int ret;

	printf("Enter main function!\n");

	ret = setjmp(buffer);
	if (ret == 0) {
		b++;
		func();
	} else if (ret == 101) {
		printf("jump back! a=%d, b=%d\n", a, b);
		exit(0);
	}
	exit(0);
}
