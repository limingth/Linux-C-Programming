#include <stdio.h>
#include <string.h>

int main(void)
{
        printf("demo my trans\n");

	while (1)
	{
		char buf[32];
		char cmd[64];	
		int p;

	
		p = fscanf(stdin, "%s", buf);
//		printf("p = %d\n", p);
		if (p < 0)
			break;

		strcpy(cmd, "");
		strcat(cmd, "./trans.rb ");
		strcat(cmd, buf);
//              printf("cmd = %s\n", cmd);
		printf("<%s> : ", buf);
		fflush(stdout);
		system(cmd);
		printf("\n");
	}

	return 0;
}
