#include <stdio.h>



	int another2;

	int another;
	int another2;

int fun()
{
	fun2();
}

int fun2()
{
	int a = 100;
	strcpy( p, "abcd" );
}

char * p = "abcd";

char p[16];
int a = 100;

0x8010; :  a b c d 

code: 0x0 - 0x100
data: 0x100 - 0x200
0x64, "abcd"

bin: 0x200 (size)
rom 

data:  base address:  ram


text: 0k - 2k
rodata: 2k - 3k
data.bin:  3k - 4k
ROM

RO: load = exec
RW: load != exec

exec > load

copy from load to exec
bootloader : text :

------
RAM: 
data: 8k - 9k
bss: 9k - 19k


stack:  32k

text.bin : 2k
rodata.bin: 1k
data.bin : 1k ( 0x64, "abcd",......) 

bootloader.bin : 4k

int a[10k]; 

rom: 0- 8k
ram: 8k - 32k

data: ram base address  


int a = 100;

{
//	a = 200;
	a = 100;
	printf( "%d", a );
	int a = 100;

}
p = 8010;

8000 -> 9000
8010: 00 00 00 00

9010

printf( "%s" , p );

int main(void)
{
	int z_g_int;
	int g_int = 100;

	fun();
	fun2();

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
