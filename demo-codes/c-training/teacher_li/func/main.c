#include <stdio.h>

#if 1
void f1()
{
	int a = 100;
	printf("a = %d \n", a);
	return ;
}

void f2()
{
	int b = 0x11223344;
//	printf("b = 0x%x \n", b);
//	printf("&b = 0x%x \n", &b);
	return ;
}
#endif

#if 0
int bar(int c, int d)
{
	return c+d;
}

int foo(int a, int b)
{
	return bar(a, b);
}
#endif

int main(void)
{
#if 1
	int a[1];
	a[-8] = 1234;
	f2();
	printf("&a = 0x%x\n", a);
	printf("a[-1] = 0x%x  0x%x\n", a[-1], a-1);
	printf("a[-1] = 0x%x\n", a[-2]);
	printf("a[-1] = 0x%x\n", a[-3]);
	printf("a[-1] = 0x%x\n", a[-4]);
	printf("a[-1] = 0x%x\n", a[-5]);
	printf("a[-1] = 0x%x\n", a[-6]);
	printf("a[-1] = 0x%x\n", a[-7]);
	printf("a[-1] = 0x%x\n", a[-8]);
	printf("a[-1] = 0x%x\n", a[-9]);
	printf("a[-1] = 0x%x\n", a[-10]);
	printf("a[-1] = 0x%x\n", a[-11]);
	printf("a[-1] = 0x%x 0x%x\n", a[-12], a-12);
	printf("a[-1] = 0x%x\n", a[-13]);
	printf("a[-1] = 0x%x\n", a[-14]);
	printf("a[-1] = 0x%x\n", a[-15]);
	printf("a[-1] = 0x%x\n", a[-16]);
	return 0;
#endif
	foo(2, 3);
	return 0;
}
