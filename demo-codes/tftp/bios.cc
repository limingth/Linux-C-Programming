#include "types.h"
#include "console.h"
#include "utils.h"
#include "39vf160.h"


#define	MAX_CMD_LEN	128
#define	MAX_ARGS	MAX_CMD_LEN/4
#define	ENTER_KEY	0x0d
#define	BACK_KEY	0x08
#define	ESC_KEY		0x1b

int IP_ADDRESS = 0xc0a8a865;

#define	DFT_DOWNLOAD_ADDR	0x8000
#define	DFT_PROGRAM_BEGIN	0
unsigned int download_addr;
unsigned int program_begin;	

const char PROMPT[] = "\\>";


int Help(int argc, char *argv[]);
int LoadFile2Mem(int argc, char *argv[]);
int ProgFlash(int argc, char *argv[]);
/************************************************/
typedef int (*cmdproc)(int argc, char *argv[]);
typedef struct {
	const char *cmd;
	const char *hlp;
	cmdproc proc;
}CMD_STRUC;

CMD_STRUC CMD_INNER[] =
				{ 
					{"help", "Display this", Help},	
					{"load", "Load file to memory at address.", LoadFile2Mem},
					{"prog", "Program flash", ProgFlash},
					{NULL, NULL, NULL}
				};

/************************************************/
int Help(int argc, char *argv[])
{
	int i;
	
	for(i=0; CMD_INNER[i].cmd!=NULL; i++)
	{
		if(CMD_INNER[i].hlp!=NULL)
		{
			putch('\n');
			printf(CMD_INNER[i].hlp);
		}
	}
	
	return 0;
}

int tftp_main(unsigned long ip, unsigned long mode, unsigned long param, unsigned long addr);

int LoadFile2Mem(int argc, char *argv[])
{
	
	if(argc<2)
	{
		download_addr = DFT_DOWNLOAD_ADDR;
		printf("\nNo begin address for download, use default address 0x%x", download_addr);
	}
	else
		download_addr = strtoul(argv[1], NULL, 0);
	
	tftp_main(IP_ADDRESS, 0, 0, download_addr);

	return 0;
}

int ProgFlash(int argc, char *argv[])
{

	if(argc<2)
	{
		printf("\nNo begin address for program!");
		return -1;
	}
	
	//prog_flash();
	
	return 0;
}

/************************************************/
static void ParseArgs(char *cmdline, int *argc, char **argv)
{
#define STATE_WHITESPACE	0
#define STATE_WORD			1

	char *c;
	int state = STATE_WHITESPACE;
	int i;

	*argc = 0;

	if(strlen(cmdline) == 0)
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

static int GetCmdMatche(char *cmdline)
{
	int i, len;
	
	len = strlen(cmdline);
	
	for(i=0;CMD_INNER[i].cmd!=NULL;i++)
	{
		if(strncmp(CMD_INNER[i].cmd, cmdline, len)==0)
			return i;
	}
	
	return -1;
}

static int ParseCmd(char *cmdline, int cmd_len)
{
	int argc, num_commands;
	char *argv[MAX_ARGS];

	ParseArgs(cmdline, &argc, argv);

	/* only whitespace */
	if(argc == 0) 
		return 0;
	
	num_commands = GetCmdMatche(argv[0]);
	if(num_commands<0)
		return -1;
		
	if(CMD_INNER[num_commands].proc!=NULL)	
		CMD_INNER[num_commands].proc(argc, argv);
				
	return 0;			
}

/************************************************/

int main()
{
	char command[MAX_CMD_LEN];
	char key;
	int i;
	unsigned short tmp[32];
	
	console_init();
	printf("\nBios for download and program.\n");
	printf("Type help for help.\n");	
	printf(PROMPT);	
	
		printf("%x", ReadSWPID());
		
		for(i = 0; i<32; i++)
			tmp[i] = 32-i;
		FlashProg(0x40080, tmp, 32);	
		SectorErase(0x40000);	
	
	i = 0;
	
	for(;;)
	{
		if(kbhit())
		{
			key = getch();
			if(key == BACK_KEY)
			{			
				i -= i?1:0;
				putch(key);
			}
			else
			if(key == ENTER_KEY)
			{
				int tmp;
				command[i] = 0;
				tmp = ParseCmd(command, i);
				printf(PROMPT);
				if(tmp<0)
					printf("Bad command.");
				i = 0;
			}
			else
			{
				if(i<MAX_CMD_LEN-1)
					command[i++] = key;
					putch(key);
			}				
		}
	}
	
}





