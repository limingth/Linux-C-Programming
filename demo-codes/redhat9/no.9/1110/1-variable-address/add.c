
int add_out_a = 1;
int add_out_b = 2;

int add( int para_a, int para_b )
{
	int add_a = 1;
	int add_b = 1;

	static int sta_a = 1;

	printf( "<add.c> address static a  = 0x%x \n", &sta_a );
	//printf( "<add.c> static a  = %d \n", sta_a );

	printf( "<add.c> address para_a = 0x%x \n", &para_a );
	printf( "<add.c> address para_b = 0x%x \n", &para_b );

	printf( "<add.c> address add_a = 0x%x \n", &add_a );
	printf( "<add.c> address add_b = 0x%x \n", &add_b );
	//return 0;
	printf( "<add.c> address add_out_a = 0x%x \n", &add_out_a );
	printf( "<add.c> address add_out_b = 0x%x \n", &add_out_b );

	return para_a + para_b;
}
