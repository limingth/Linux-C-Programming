/*
 *	shell.h    -    header file of shell
 *	
 *	Author: 	yu feng <progeryf@gmail.com>
 *	Date:		2007-5-27
 */
/* the file will be downloader here*/
#define  DOWNLOAD_BIN_ADDR	0x8000
/* first 64K (0x10000) is used for bootloader
 * from 0x10000(64K) - 0x200000(2M) is used for user boot image
 */
#define	__ROM_SIZE	0x200000
/* the size of bootloader you can read and write from here*/
#define	BIOS_BASE	(__ROM_SIZE-0x1f8000)
/* the address where user can use*/
#define	BIOS_LOAD	(__ROM_SIZE-0x8000)

void shell_command( void );

char shell_getchar( void );

char shell_putchar( char ch );

int shell_gets( char * buf );

int shell_readline( char * buf );
