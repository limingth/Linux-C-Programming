#include <stdio.h>
#include <termios.h>
#include <string.h>
#include "int.h"


int int_get_status(void)
{
#ifdef TARGET_PC
	/* pc simulate int0 input */
	struct termios oldbuf, buf;
	char c;
	int int_value = 0;
	
	setvbuf(stdin, (char *)NULL, _IONBF, 0);

	if (tcgetattr(0, &buf) < 0)
		 return(1);
	oldbuf = buf;
	buf.c_lflag &= ~(ECHO|ICANON);
	if (tcsetattr(0, TCSAFLUSH, &buf) < 0)
		return(-1);
	c = getchar();
	//putchar(c);
	if (tcsetattr(0, TCSAFLUSH, &oldbuf) < 0)
		return(-1);

	switch(c)
	{
		case '`': 
			int_value = 1;
			break;
		default:
			int_value = 0;
			break;
	}
	return int_value;
#else
	/* add your led driver code here */

#endif
	
	return 0;
}

