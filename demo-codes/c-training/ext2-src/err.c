#include "common.h"

void err_sys(const char *str)
{
	perror(str); exit(1);
}

void err_usr(const char *str)
{
	fputs(str, stderr); exit(0);
}
