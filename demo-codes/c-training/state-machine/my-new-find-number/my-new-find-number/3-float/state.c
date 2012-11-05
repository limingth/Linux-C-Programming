/*
 * find signed int number in string
 *
 * 2010-3-30	li ming <limingth@akaedu.org>
 *
 */

#include <stdio.h>

//char str[100] = "abc+1.23+.ab-.-12..+c..99-.+.99+";
char str[100] = 
"aa" "a+" "a9" "a." 
"+a" "++" "+9" "+." 
"9a" "9+" "99" "9."
".a" ".+" ".9" ".."
"+.a" "+.+" "+.9" "+.."
"9.a" "9.+" "9.9" "9.."
".9a" ".9+" ".99" ".9." ".."
"+.9a" "+.9+" "+.99" "+.9." "+.."
;

char ch;
char result[50][100];
int row = 0;
int col = 0;

/*
 * define input char type
 *
 * 0: 'a'-'z'/else like !@#$%^&*()
 * 1: '+'/'-'
 * 2: '0'-'9'
 * 3: '.'
 * 4: '\0'
 */
int get_input_type(char c)
{
	if (c == '+' || c == '-')
		return 1;

	if (c >= '0' && c <= '9')
		return 2;

	if (c == '.')
		return 3;

	if (c == '\0')
		return 4;

	return 0;
}

void action_null()
{
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

void action_zero_save()
{
	col = 0;
	result[row][col++] = ch;
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
 * FSM state 
 *
 * 0: (a) start state or restart state without digit 
 * 1: (a+/+) get sign +/-
 * 2: (+9/9) get digit before point 
 * 3: (+./.) get point directly
 * 4: (+9./9.) get point after digit
 * 5: (+9.9/9.9) get digit after point
 * -1: end state
 *
 */

int state_transition_table[6][5] =
{
	{0, 1, 2, 3, -1},
	{0, 1, 2, 3, -1},
	{0, 1, 2, 4, -1},
	{0, 1, 5, 3, -1},
	{0, 1, 5, 3, -1},
	{0, 1, 5, 3, -1},
};

void (*action[6][5])(void) =
{
	{action_null, action_save, action_save, action_save, action_null},
	{action_back, action_back_save, action_save, action_save, action_back},
	{action_found, action_found_save, action_save, action_save, action_found},
	{action_back, action_zero_save, action_save, action_zero_save, action_back},
	{action_found, action_found_save, action_save, action_found_save, action_found},
	{action_found, action_found_save, action_save, action_found_save, action_found},
};

int main(void)
{
	int i;
	int input;
	int state = 0;

	printf("state machine demo \n");
	printf("please input a float string: ");
	//scanf("%s", str);

	printf("your input str : %s\n", str);

	i = 0;
	state = 0;

	while (state != -1)
	{
	//	printf("state = %d \n", state);
	
		ch = str[i];
		input = get_input_type(ch);

	//	printf("ch = %c  input = %d\n", ch, input);
	
		action[state][input]();

		state = state_transition_table[state][input];

		i++;
	}

	printf("there is %d number in string %s \n", row, str);
	for (i = 0; i < row; i++)
		printf( "%s \n", result[i] );

	return 0;
}
