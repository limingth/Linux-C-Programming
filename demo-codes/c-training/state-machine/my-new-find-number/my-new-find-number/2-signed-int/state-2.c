/*
 * find signed int number in string
 *
 * 2010-3-30	li ming <limingth@akaedu.org>
 *
 */

#include <stdio.h>

char str[100] = "abc+123ab--12+c99-99+";

char ch;
char result[10][100];
int row = 0;
int col = 0;

/*
 * define input char type
 *
 * 0: 'a'-'z'/else like !@#$%^&*()
 * 1: '+'/'-'
 * 2: '0'-'9'
 * 3: '\0'
 */
int get_input_type(char c)
{
	if (c == '\0')
		return 3;

	if (c >= '0' && c <= '9')
		return 2;

	if (c == '+' || c == '-')
		return 1;

	return 0;
}

void action_save()
{
	result[row][col++] = ch;
	return;
}

void action_back()
{
	col--;
	result[row][col] = '\0';
	return;
}

void action_found()
{
	result[row][col] = '\0';
	row++;
	col = 0;
}

void action_back_save()
{
	action_back();
	action_save();
}

void action_found_save()
{
	action_found();
	action_save();
}

/*
 * FSM - finite state machine
 *
 * state 0: start state (a/)
 * state 1: get a sign (+/-)
 * state 2: get a digit (+9/9)
 * state -1: end state (get '\0')
 *
 *	input
 * S	0('a')	1('+')	2('9')	3('\0')
 * 0:	0	1	2	-1
 * 1:	0	1	2	-1
 * 2:	0	1	2	-1
 * -1:	-	-	-	-
 */

int main(void)
{
	int i;
	int input;
	int state = 0;


	printf("state machine demo \n");

	printf("input str : %s\n", str);

	i = 0;
	state = 0;

	while (state != -1)
	{
	//	printf("state = %d \n", state);

		ch = str[i];
		input = get_input_type(ch);

	//	printf("ch = %c  input = %d\n", ch, input);

		switch (state)
		{
		case 0:
			switch (input)
			{
			case 0:	// "aa"
				state = 0;
				break;
			case 1:	// "a+"
				state = 1;
				action_save();
				break;
			case 2:	// "a9"
				state = 2;
				action_save();
				break;
			case 3:	// "a'\0'"
				state = -1;
				break;
			 }
			break;
		case 1:
			switch (input)
			{
			case 0:	// "+a"
				state = 0;
				action_back();
				break;
			case 1:	// "++"
				state = 1;
				action_back_save();
				break;
			case 2:	// "+9"
				state = 2;
				action_save();
				break;
			case 3:	// "+'\0'"
				state = -1;
				action_back();
				break;
			 }
		    break;

		case 2:
			switch (input)
			{
			case 0: // "9a"
				state = 0;
				action_found();
				break;
			case 1:	// "9+"
				state = 1;
				action_found_save();
				break;
			case 2:	// "99"
				state = 2;
				action_save();
				break;
			case 3:	// "9'\0'"
				state = -1;
				action_found();
				break;
			 }
		    break;

		case -1:
		    break;
		default:
		    break;
		}

		i++;
	    }

	printf("there is %d number in string %s \n", row, str);
	for (i = 0; i < row; i++)
		printf( "%s \n", result[i] );

	return 0;
}
