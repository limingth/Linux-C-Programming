#include <stdio.h>

char str[100] = "abc123ab12c9999";

/*
 * define input char type
 *
 * 0: 'a'-'z'/else like !@#$%^&*()
 * 1: '0'-'9'
 * 2: '\0'
 */
int get_input_type(char c)
{
	if (c == '\0')
		return 2;

	if (c >= '0' && c <= '9')
		return 1;

	return 0;
}

/*
 * FSM - finite state machine
 *
 * state 0: start state (a/)
 * state 1: get a digit (a9/9)
 * state -1: end state (get '\0')
 *	input
 * S	0(a)	1(9)	2('\0')
 * 0:	0	1	-1
 * 1:	0	1	-1
 * -1:	-	-	-
 */

int main(void)
{
	int i;
	int input;
	char ch;
	int state = 0;

	char result[10][100];
	int row = 0;
	int col = 0;

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
			case 0:
				state = 0;
				break;
			case 1:
				state = 1;
		//		printf("first digit found! \n");
				printf("%c", ch);
				result[row][col++] = ch;
				break;
			case 2:
				state = -1;
				break;
			default:
				break;
			 }

			break;
		case 1:
			switch (input)
			{
			case 0:
				state = 0;
		//		printf("a whole number found! \n");
				printf("\n");
				result[row][col] = '\0';
				row++;
				col = 0;
				break;
			case 1:
				state = 1;
		//		printf("next digit found! \n");
				printf("%c", ch);
				result[row][col++] = ch;
				break;
			case 2:
				state = -1;
				printf("\n");
				result[row][col] = '\0';
				row++;
				col = 0;
				break;
			default:
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
