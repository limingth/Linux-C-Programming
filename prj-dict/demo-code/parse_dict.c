#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#akaedu'\n'
Trans: meaning\n
*/
int get_input_type(char c)
{
	if (c == '#')
		return 1;

	if (c == '\n')
		return 2;

	return 0;
}

/*
 		state machine design

	input:	0('a')		1('#')		2('\n')
---------------------------------------------
state:
0: " "		0			1			0
1: "#"		1(#a)		0(err)		2(#a\n)
2: "#a\n"	2			0(err)		0(ok)
*/
// int main(void)
int parse_dict(char * filename, void(*callback)(char *, char *))
{
	int i = 0;
	int j = 0;
	int counter = 0;

	int state = 0;	// init state
	int input = 0;	// 0: space		1: alpha	2: digit

	char word[64];
	char meaning[256];

	FILE * fp;

	printf("begin to parse dict file!\n");

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("file %s doesn't exist!\n", filename);
		exit(0);
	}

	while (1)
	{
		char c;

		//c = getchar();
		c = fgetc(fp);
		if (c == EOF)
			break;

		input = get_input_type(c);
		//printf("state = %d ", state);

		switch (state)
		{	
		case 0:		//" "
			switch (input)
			{
			case 0:
				break;

			case 1:
				state = 1;
				i = 0;
				//printf("word begin with <%c>\n", c);
				break;

			case 2:
				state = 0;
				//printf("word begin with <%c>\n", c);
				break;

			default:
				break;
			}
			break;

		case 1:		// "#"
			switch (input)
			{
			case 0:
				word[i++] = c;
				state = 1;
				break;

			case 1:
				state = 0;
				break;

			case 2:
				word[i] = '\0';
				counter++;
				//printf("%d ", counter);
				//printf("word found! value = <%s>\n", word);
				j = 0;
				state = 2;
				break;

			default:
				break;
			}
			break;

		case 2:		// "9"
			switch (input)
			{
			case 0:
				meaning[j++] = c;
				state = 2;
				break;

			case 1:
				state = 0;
				break;

			case 2:
				meaning[j] = '\0';
				//printf("meaning found! value = <%s>\n", meaning);
				callback(word, meaning);
				state = 0;
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	fclose(fp);
	printf("parse dict file finished!\n");

	return 0;
}
