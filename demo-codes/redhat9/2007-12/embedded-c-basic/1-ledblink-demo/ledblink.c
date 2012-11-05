void delay ( void )
{
	int i;
	for( i = 0 ; i < 1000000 ; i++)
		;
	return ;
}

int main( void )
{
	volatile unsigned int * iopmod = (volatile unsigned int *)0x03ff5000;
	volatile unsigned int * iopdata = (volatile unsigned int *)0x03ff5008;

	*iopmod = *iopmod | 0x00020070;
	*iopdata = 0x00000000;

	while(1)
	{
		*iopdata |= 0x00020070;
		delay ();
		*iopdata &= (~0x00020070);
		delay ();
	}

	return 0;
}
