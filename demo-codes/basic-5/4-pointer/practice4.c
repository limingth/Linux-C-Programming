#include <stdio.h>

void swap(int * pa, int * pb)
{
	int tmp;

	tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

void sort1(int * p, int * q)
{
	while (1)
	{
		while (*p % 2 == 1)
			p++;

		while (*q % 2 == 0)
			q--;

		if (p > q)
			break;

		swap(p, q);

		p++;
		q--;
	}

	return;
}

void sort2(int * p, int * q)
{
	while (p < q)
	{
		if (*p % 2 == 1)
		{
			p++;
			continue;
		}

		if (*q % 2 == 0)
		{
			q--;
			continue;
		}

		swap(p, q);

		p++;
		q--;
	}

	return;
}

void sort3(int * p, int * q)
{
	while (p < q)
	{
		if (*p % 2 == 0 && *q % 2 == 1)
			swap(p++, q--);

		if (*p % 2 == 1)
			p++;

		if (*q % 2 == 0)
			q--;
	}

	return;
}

void sort4(int * p, int * q)
{
	if (p > q)
		return;

	if (*p % 2 == 0 && *q % 2 == 1)
		swap(p, q);

	if (*p % 2 == 1)
		p++;

	if (*q % 2 == 0)
		q--;
	
	sort4(p, q);
}

int main(void)
{
	int a[] = {22, 4, 3, 7, 50, 8, 11, 2, 17, 15};
	int size = sizeof(a)/sizeof(a[0]);

	int * p = a;
	int * q = a + size - 1;

	int i = 0;

	for (i = 0; i < size; i++)
		printf("%d ", a[i]);
	printf("\n");
	
	sort4(p, q);

	for (i = 0; i < size; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
