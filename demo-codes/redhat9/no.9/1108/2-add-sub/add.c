#include <stdio.h>

#include "add.h"

int add_test = 100;

int add2(int a, int b)
{
	return (2*add(a,b));
}

int add(int a, int b)
{
	return (a + b);
}


