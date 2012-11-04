// ”猜数游戏“参考代码 － 用户猜数

#include <stdio.h>

#define		N	3

void get_rand_num(int n, char * guess)
{
	int counter = 0;
	int digit = 0;
	int flag = 0;

	srand(time(NULL));

	while (counter < n)
	{
		// get a rand digit in 0-9
		digit = rand() % 10;

		if (!(flag & (1<<digit)))
		{
			*guess = digit + '0';

			guess++;
			counter++;

			// set flag bit_n = 1
			flag |= 1<<digit;
		}
	}
	
	return;
}

void get_input_num(int n, char * input)
{
	scanf("%s", input);

	*(input+N) = '\0';

	return;
}

void comp_str(char * pa, char * pb, int * na, int * nb)
{
	int i, j;

	*na = 0;
	*nb = 0;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			if (pa[i] == pb[j])
			{
				if (i == j)
					(*na)++;
				else
					(*nb)++;
			}
		}

	return;
}

int main(void)
{
	char guess[N+1] = "39";
	char input[N+1];
	int na = 0, nb = 0;
	int counter = 0;

	printf("hello, guess num\n");

	get_rand_num(N, guess);
//	printf("guess num = %s\n", guess);

	while (1)
	{
		counter++;

		printf("please input %d digits:", N);
		get_input_num(N, input);
		printf("input num = %s\n", input);

		// compare two string, return nA, nB;
		comp_str(guess, input, &na, &nb);
//		printf("str1: %s\n", guess);
		printf("%d str2: %s\n", counter, input);
		printf("%dA, %dB\n", na, nb);

		if (na == N)
			break;
	}

	printf("You win! congratulation! game over!\n");

	return 0;
}

// ”猜数游戏“参考代码 － 电脑猜数

#include <stdio.h>

//#define	N	2
//#define	ALL	(10*10)
//#define	N	3
//#define	ALL	(10*10*10)
#define	N	4
#define	ALL	(10*10*10*10)
//#define	N	5
//#define	ALL	(10*10*10*10*10)

void get_rand_num(int n, char * guess)
{
	int counter = 0;
	int digit = 0;
	int flag = 0;

	srand(time(NULL));

	while (counter < n)
	{
		// get a rand digit in 0-9
		digit = rand() % 10;

		if (!(flag & (1<<digit)))
		{
			*guess = digit + '0';

			guess++;
			counter++;

			// set flag bit_n = 1
			flag |= 1<<digit;
		}
	}
	
	return;
}

void num_to_str(int num, char * str, int n)
{
	int rest;
	int i = 0;
	char * p = str;
	
	while (num > 0)
	{
		rest = num % 10;
		*p++ = rest + '0';
		num /= 10;
	}

	while (p - str < n)
		*p++ = '0';
	*p= '\0';

	for (i = 0; i < n / 2; i++)
	{
		char tmp;
		tmp = str[i];
		str[i] = str[n-1-i];
		str[n-1-i] = tmp;
	}

	return;
}

int check_same_digit(char * str, int n)
{
	int i, j;

	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
		{
			if (str[i] == str[j])
				return 1;
		}

	return 0;
}

int find_first_num(int p[])
{
	int i = 0;

	for (i = 0; i < ALL; i++)
		if (p[i] == 1)
			return i;

	return -1;
}

void comp_str(char * pa, char * pb, int * na, int * nb)
{
	int i, j;

	*na = 0;
	*nb = 0;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			if (pa[i] == pb[j])
			{
				if (i == j)
					(*na)++;
				else
					(*nb)++;
			}
		}

	return;
}

int check_all_possible(char * src, int na, int nb, int p[])
{
	int i = 0;
	char dst[N+1];
	int new_na, new_nb;

	for (i = 0; i < ALL; i++)
	{
		if (p[i] == 0)
			continue;

		// i -> string dst;
		num_to_str(i, dst, N);

		comp_str(src, dst, &new_na, &new_nb);

		if (new_na != na || new_nb != nb)
			p[i] = 0;
	}

	return 0;
}

int main(void)
{
	int i = 0;
	char str[N+1];
	int possible[ALL];
	int counter = 0;

	char your_num[N+1] = "1234";

	printf("hello, pc guess num \n");
	//scanf("%s", your_num);
	get_rand_num(N, your_num);
	printf("your num: %s\n", your_num);
	
	for (i = 0; i < ALL; i++)
	{
		//printf("i = %d, ", i);

		num_to_str(i, str, N);

		if (check_same_digit(str, N))
			possible[i] = 0;
		else
			possible[i] = 1;

		//printf("str = %s, p = %d \n", str, possible[i]);
	}

	while (1)
	{
		int guess = find_first_num(possible);
		char guess_str[N+1];
		int na = 0, nb = 0;

		printf("guess = %d\n", guess);
		num_to_str(guess, guess_str, N);
		printf("guess str = %s\n", guess_str);

		comp_str(guess_str, your_num, &na, &nb);
		printf("hint: %da, %db\n", na, nb);

		printf("please tell me ?A?B \n");
		//scanf("%da%db", &na, &nb);
		counter++;
		printf("%d: na = %d, nb = %d \n", counter, na, nb);
		if (na == N)
			break;

		check_all_possible(guess_str, na, nb, possible);
	}

	printf("haha, I win!\n");
	
	return 0;
}