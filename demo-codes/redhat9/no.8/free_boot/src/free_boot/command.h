/*
 *	command.h   -  header file of shell command
 *	
 *	Author: 	yu feng<progeryf@gmail.com>
 *	Date:		2007-5-27
 */


void help( void );

int go(int argc, char* argv[]);

int dump(int argc, char* argv[]);


//int flashw(int argc, char* argv[]);
int flashl(unsigned read_addr, unsigned download_addr, unsigned offset);

int flashw(unsigned write_addr, unsigned download_addr, unsigned offset);
//int flashl(int argc, char* argv[]);
