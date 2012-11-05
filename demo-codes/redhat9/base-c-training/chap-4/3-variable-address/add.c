
int adda = 1;
int addb = 2;

int add( int a, int b )
{
	int aa = 1;
	int bb = 1;

	static int sta_a = 1;

	printf( "<add.c> address static a  = 0x%x \n", &sta_a );
	printf( "<add.c> static a  = %d \n", sta_a );

	printf( "<add.c> address a = 0x%x \n", &a );
	printf( "<add.c> address b = 0x%x \n", &b );

	printf( "<add.c> address aa = 0x%x \n", &aa );
	printf( "<add.c> address bb = 0x%x \n", &bb );

	printf( "<add.c> address adda = 0x%x \n", &adda );
	printf( "<add.c> address addb = 0x%x \n", &addb );

	return a+b;
}
