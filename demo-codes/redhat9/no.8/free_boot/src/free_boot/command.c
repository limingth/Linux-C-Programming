/*
 *	command.c   -   shell command implementation
 *	
 *	Author: 	yu feng <progeryf@gmail.com>
 *	Date:		2007-5-27
 */

#include "my_string.h"
#include "my_printf.h"
#include "shell.h"
#include "command.h"
#include "flash_39vf160.h"


void help( void )
{
	my_printf( "\rhelp     - list of commands in this shell \n" );	
	my_printf( "\rdown     - download uue file to 0x8000  \n" );
	my_printf( "\rgo       - run program at 0x8000 \n" );	
	my_printf( "\rflashw   - write progarm to flash \n" );	
	my_printf( "\rflashl   - load program from flash  \n" );	
	my_printf( "\rdump     - anylysis the memory \n" );	

	return ;
}

int  go(int argc, char* argv[])
{
	unsigned current_pc;	
	
	if (argc != 2)
	{
		my_printf("\r please input the right parameter\n");
		my_printf("\r go 0x8000\n");
		return -1;
	}

	my_printf( "\r<go>: to run code from 0x%x. \r\n", my_atoi(argv[1]));	
	
	current_pc = my_atoi(argv[1]);

	((void (*)(void))(current_pc))();

	return 0;
}


#define  DOWNLOAD_BIN_ADDR	0x00008000

int cistreq(char *s, char *t, int term)
{
	for ( ; ((*s | 0x20) == (*t | 0x20)) || (*s <= term && *t <= term); s++, t++)
	if (*s <= term)
		return 1;
    	return 0;
}

char *nextword(char *word)
{
	while (*word > ' ') word++;
	while (*word == ' ') word++;
	return word;
}

#define BEGIN "begin"
#define END   "end"

int uue_receive(int argc, char* argv[])
{
	char *buffer = (char *)DOWNLOAD_BIN_ADDR;
	char *s;
	int errs = 0;
	int i;
	unsigned c, w;
	int offset = 0;
	int len; 
	
	char command_line[256];
	char gpbuff[256];

	my_printf("Ready to download. Use 'transmit' option on terminal emulator to download file. \n");
	s = command_line;
	do 
	{    	
		if (shell_readline(s) == -1)
			return -1;	
	} while (!cistreq(s, BEGIN, ' '));

	s = nextword(s);
	s = nextword(s);
	my_strcpy(gpbuff, s);
	
	do 
	{
		s = command_line;
		len = shell_readline( s );
		
		if (len == -1 || cistreq(s, END, ' '))
			break;
		c = *s++;
		
		if (!c) continue;
		len = c - 0x20;
		if (len == 0) continue;
		if (len > 45) { errs++; continue; }
		i = 0;
		while (1) 
		{
			c = *s;
			if (c) 
			{
				c -= 0x20;
				if (c >= 0x40) { errs++; break; }
				s++;
			}
			w = (w << 6) + c;
			if ((++i & 3) == 0) 
			{
				buffer[offset++] = w >> 16;
				if (--len == 0) break;
				buffer[offset++] = w >> 8;
				if (--len == 0) break;
				buffer[offset++] = w;
				if (--len == 0) break;			
			}
		}
	} while (1);
	
	if (errs)
		my_printf("Error: %d errors encountered during download. \n", errs);
	my_printf("Loaded file %s at address %x, size = %d \n", gpbuff, (int)buffer, offset);
	return 0;
}

int dump(int argc, char* argv[])
{
	int i = 0;
	unsigned char * address;
	
	address = (unsigned char *)my_atoi(argv[1]);

	if (argc != 3)
	{
		my_printf("\r please input the right parameter\n");
		return -1;
	}
	
	for( i = 0; i < my_atoi(argv[2]); i++)
	{
		if(i%16 == 0)
			my_printf("0x%x: ", i+address);
		my_printf("%x ",*(address+i));
		if((i+1)%16 == 0 )
			my_printf("\r\n");
	}

	return 0;
}
/*
 * write the flash 
 * read from DOWNLOAD_BIN_ADDR write to 0x1000000+0x8000
 */
int flashw(unsigned write_addr, unsigned download_addr, unsigned offset)
{
	my_printf( "write memory program to flash, size = 0x%x \r\n", offset );	
	SectorProg(write_addr, (unsigned short *)download_addr, offset);	
	return 0;
}

/*
 * load the file from flash 
 * read from 0x1000000+0x8000 copy to DOWNLOAD_BIN_ADDR
 */
int flashl(unsigned read_addr, unsigned download_addr, unsigned offset)
{
	my_printf( "load flash program to mem, size = 0x%x \r\n", offset );
	FlashRead(read_addr, (unsigned short *)download_addr, offset );
	return 0;
}
