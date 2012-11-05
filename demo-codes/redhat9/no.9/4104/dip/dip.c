#include <stdio.h>
#include <termios.h>
#include <string.h>
#include "dip.h"

static int dip_value = 0;

int dip_get_value(void)
{
#ifdef TARGET_PC
	/* pc simulate dip input */
	struct termios oldbuf, buf;
	char c;
	
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
		case '1': 
			dip_value |= 1 << 3;
			break;
		case '2': 
			dip_value |= 1 << 2;
			break;
		case '3': 
			dip_value |= 1 << 1;
			break;
		case '4': 
			dip_value |= 1 << 0;
			break;
		case 'q': 
			dip_value &= ~(1 << 3);
			break;
		case 'w': 
			dip_value &= ~(1 << 2);
			break;
		case 'e': 
			dip_value &= ~(1 << 1);
			break;
		case 'r': 
			dip_value &= ~(1 << 0);
			break;
		default:
			break;
	}
	return dip_value;
#else
	/* add your led driver code here */

#endif
	
	return 0;
}

