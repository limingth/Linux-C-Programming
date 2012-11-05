#include <stdio.h>

int get_input_type( char c )
{
	if( c >= '0' && c <= '9' )
		return 1;

	if( c == '\0' )
		return 2;

	return 0;
}


int main(void)
{
	char str[100] = "abc123ab12ab11";
	char result[10][50];
	int row, col;

	int i = 0;
	char c;
	int input; 
	int oldtype;

	int state = 0;

	printf("demo state machine \n");
	printf("please input a string: \n");
	scanf("%s", str);

	printf("string number is %s \n", str);
	printf("%s\n", str);

	/* init start state = 0 */
	state = 0;
	while( state != -1 )
	{
		c = str[i];
		//printf("%c", c);
	
		input = get_input_type( c );
		//printf("%d", input);

		switch(state)
		{
		case 0:
			switch(input)
			{
			case 0:
				state = 0;
				break;
			case 1:
				state = 1;
				printf("%c", c);
				break;
			case 2:
				state = -1;
				break;
			}

			break;
		case 1:
			switch(input)
			{
			case 0:
				state = 0;
				printf("\n");
				break;
			case 1:
				state = 1;
				printf("%c", c);
				break;
			case 2:
				state = -1;
				printf("%c", c);
				printf("\n");
				break;
			}
			break;
		case -1:
			break;
		}
		
	//	printf("(%d)", state);
#if 0
		if (type == 1)
		{
			printf("%c", c);
		}

		if (type == 0 && oldtype == 1)
		{
			printf("\n");
			row++;
		}
#endif
		i++;
	}

	printf("\n");
//	printf("there is %d number in string. \n", row+1);

	return 0;
}
