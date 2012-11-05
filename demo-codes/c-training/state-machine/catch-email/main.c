#include <stdio.h>

/*
 * input type:
 *
 * 0: else
 * 1: 'a-z'
 * 2: '0-9'
 * 3: '@'
 * 4: '.'
 * 5: '-'/'_'
 * 6: '\0'
 */
int get_input_type( char c )
{
	if ( c >= 'a' && c <= 'z' )
		return 1;
	if ( c >= 'A' && c <= 'Z' )
		return 1;

	if ( c >= '0' && c <= '9' )
		return 2;

	if ( c == '@' )
		return 3;

	if ( c == '.' )
		return 4;

	if ( c == '_' || c == '-' )
		return 5;

	if ( c == '\0' )
		return 6;

	return 0;
}

char c;

void action_save(void)
{
	printf("%c", c);
}

void action_found(void)
{
	printf("\n");
}

void action_zero(void)
{
	printf("\r");
}

void action_found_save(void)
{
	action_found();
	action_save();
}

void action_back(void)
{
	printf("\b");
}

void action_back_save(void)
{
	action_back();
	action_save();
}

void action_null(void)
{
}

/*
 * 0: else
 * 1: 'a-z'
 * 2: '0-9'
 * 3: '@'
 * 4: '.'
 * 5: '-'/'_'
 * 6: '\0'
 */

void (*action[6][7])(void) = 
{
	action_null, action_save, action_save, action_null, action_null, action_null, action_null,	
	action_zero, action_save, action_save, action_save, action_save, action_save, action_zero,	
	action_zero, action_save, action_save, action_zero, action_zero, action_zero, action_zero,	
	action_zero, action_save, action_save, action_zero, action_save, action_save, action_zero,	
	action_zero, action_save, action_save, action_zero, action_zero, action_zero, action_zero,	
	action_found, action_save, action_save, action_zero, action_save, action_save, action_found,	
};

/*
 *		input
 *	S	0(' ')	1(a)	2(9)	3(@)	4(.)	5(-/_)	6(\0)
 *	0:	0	1	1	0	0	0	-1	
 *	1:a	0	1	1	2	1	1	-1
 *	2:a@	0	3	3	0	0	0	-1
 *	3:a@a	0	3	3	0	4	3	-1
 *	4:a@a.	0	5	3	0	0	0	-1
 *	5:a@a.a	0	5	3	0	4	3	-1
 *
 */
int s_table[6][7] =
{
	0, 1, 1, 0, 0, 0, -1,	
	0, 1, 1, 2, 1, 1, -1,	
	0, 3, 3, 0, 0, 0, -1,	
	0, 3, 3, 0, 4, 3, -1,	
	0, 5, 3, 0, 0, 0, -1,	
	0, 5, 3, 0, 4, 3, -1,	
};

char str[10000] = "abc123ab12ab11";
char filename[100];

int main(void)
{
	char result[10][50];
	int row, col;

	int i = 0;
	int input; 
	int oldtype;

	int state = 0;

	printf("demo state machine \n");
	printf("please input a string: \n");
	//scanf("%s", str);
	scanf("%s", filename);
	read_file( filename, str );

	printf("string number is %s \n", str);

	printf("result string is \n");
	printf("-----------------------------------------\n");
	/* init start state = 0 */
	state = 0;
	while( state != -1 )
	{
		c = str[i];
		//printf("%c", c);
	
		input = get_input_type( c );
		//printf("%d", input);

		action[state][input]();

		state = s_table[state][input];

		i++;
	}

	//printf("\n");
//	printf("there is %d number in string. \n", row+1);

	return 0;
}
