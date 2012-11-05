#include <stdio.h>

int main(void)
{
	int g_int = 100;
	int z_g_int;

	const int c_int = 200;
	const int z_c_int;

	static int s_int = 300;
	static int z_s_int;

	printf( "&c_int = 0x%x \n", &c_int );
	printf( "&g_int = 0x%x \n", &g_int );
	printf( "&s_int = 0x%x \n", &s_int );
	printf( "&z_g_int = 0x%x \n", &z_g_int );
	printf( "&z_c_int = 0x%x \n", &z_c_int );
	printf( "&z_s_int = 0x%x \n", &z_s_int );
 
	return 0;
}
