/*
 *	shell.c    -    demo of shell command
 *	
 *	Author: 	yu feng <progeryf@gmail.com>
 *	Date:		2007-5-27
 */

#include "my_string.h"
#include "my_printf.h"
#include "command.h"
#include "uart.h"
#include "xmodem.h"
#include "shell.h"

/*get a char from shell*/
char shell_getchar()
{
	char tempch;
	uart_getchar( UART0_BASE, &tempch );
	return tempch;
}

/*put a char to shell*/
char shell_putchar( char ch )
{
	uart_putchar( UART0_BASE, ch );	
	return ch;
}

/* shell get a line from user input to uart0 */
int shell_gets( char * buf )
{
	register char c;
	register char * s;
	
	for (s = buf; ((c = shell_getchar()) != '\n') && (c != '\r'); )
	{	
		if(c == '\b') 	//back space
	        {
	        	if(s > buf)
	        	{
		        	shell_putchar( '\b' );
		        	shell_putchar( ' ' );
		        	shell_putchar( '\b' );
	        		s--;
	        	}
	        	else
	        	{				
				shell_putchar( '\a' );		// Attention bell
			}
	        }
	        else 	//echo back
		{
			shell_putchar( c );
	            	*s++ = c;
		}
	}
	
	shell_putchar( '\r' );	// echo a new line back
	shell_putchar( '\n' );	
	*s = '\0';
	
	return (s-buf);
}

/* shell get a line from user input to uart0 */
int shell_readline( char * buf )
{
	register char c;
	register char * s;
	
	// do not echo
	for (s = buf; ((c = shell_getchar()) != '\n') && (c != '\r'); *s++ = c)	;
	
	*s = '\0';
	
	return (s-buf);
}

static void get_arg(char *cmdline, int *argc, char **argv)
{
#define STATE_WHITESPACE	0
#define STATE_WORD			1

	char *c;
	int state = STATE_WHITESPACE;
	int i;

	*argc = 0;

	if(my_strlen(cmdline) == 0)
		return;

	/* convert all tabs into single spaces */
	c = cmdline;
	while(*c != '\0')
	{
		if(*c == '\t')
			*c = ' ';
		c++;
	}
	
	c = cmdline;
	i = 0;

	/* now find all words on the command line */
	while(*c != '\0')
	{
		if(state == STATE_WHITESPACE)
		{
			if(*c != ' ')
			{
				argv[i] = c;		//½«argv[i]Ö¸Ïòc
				i++;
				state = STATE_WORD;
			}
		}
		else
		{ /* state == STATE_WORD */
			if(*c == ' ')
			{
				*c = '\0';
				state = STATE_WHITESPACE;
			}
		}
		c++;
	}
	
	*argc = i;
#undef STATE_WHITESPACE
#undef STATE_WORD
}

/* an endless loop for shell command interpreter */	
void shell_command( void )
{
	char command_buf[256];
	int offset;
	int argc;
	char *argv[4];

	
	while( 1 )
	{
		// Prompt of lumit shell
		my_printf( "\rFree-boot-test> " );	

		// empty the command buffer
		my_strcpy( command_buf, "" );

		// get a line from user input
		shell_gets( command_buf );
	
		get_arg(command_buf, &argc, argv);
		
		my_printf( "\rGet Command: <%s> [len=%d] \n\r", argv[0], my_strlen(argv[0]) );
		
		// compare if we can interprete this command 
		if( my_strcmp( argv[0], "help" ) == 0 )
			help();
		else 
		if( my_strcmp( argv[0], "down" ) == 0 )
			offset = xmodem_receive(argc, argv);
		else 
		if( my_strcmp( argv[0], "dn" ) == 0 )
			offset = uue_receive(argc, argv);
		else 
		if( my_strcmp( argv[0], "go" ) == 0 )
			go(argc, argv);			
		else 
		if( my_strcmp( argv[0], "dump" ) == 0 )
			dump(argc, argv);			
		else
		if( my_strcmp( argv[0], "flashw" ) == 0 )
		{
			if (argc == 1)
				flashw(BIOS_BASE, DOWNLOAD_BIN_ADDR, offset);
			else
			if (argc == 3)
				flashw(my_atoi(argv[1]), my_atoi(argv[2]), offset);
		}
		else
		if( my_strcmp( argv[0], "flashl" ) == 0 )
		{
			if (argc == 1)	
				flashl(BIOS_BASE, DOWNLOAD_BIN_ADDR, BIOS_LOAD);
			else
			if (argc == 4)
				flashl(my_atoi(argv[1]), my_atoi(argv[2]), my_atoi(argv[3]));
		}
		else
		if( my_strlen( argv[0] ) != 0 )
			my_printf( "\rUnknow Command! \n" );
		
	}
	return;
}
