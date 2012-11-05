#include "my_string.h"

int main()
{

	char* a = "0x8000";
	char* d = "10000";
	char buf[10];
	int b,c ;
	b = my_atoi (a);
	c = my_atoi (d);
	printf("%i\n",b);
	printf("%i\n",c);
}
