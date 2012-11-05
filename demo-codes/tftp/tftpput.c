#include "tftpput.h"
#include "bioscall.h"
#include "console.h"
#include "utils.h"

extern int DownLoadEnd;
extern int DownLoadOnly;
extern unsigned long LoadLength;
extern unsigned long load_addr;

static unsigned char *buf;
static int data_len;

int tftp_put_begin(void)
{
	
	puts("Starting the TFTP download...\n");
	buf = (unsigned char *)load_addr;
	data_len = 0;
	
	return 0;
}

int tftp_put(unsigned char *data, int len)
{
	static int count = 0;

	count += len;
	if (count > 32 * 1024) {
		putch('.');
		count = 0;
	}
	
	memcpy(buf + data_len, data, len);
	data_len += len;
	
	return 0;
}

int update_bios(unsigned char *bios, int size)
{

	return 0;
}

int update_system_table(unsigned char *system_table, int size)
{
	return 0;
}

int update_partition_table(unsigned char *partition_table, int size)
{
	return 0;
}

int update_partition(int partition_num, unsigned char *partition_data, int size)
{
	return 0;
}

int update_firmware(unsigned char *firmware, int size)
{
	return 0;
}

int tftp_put_end(void)
{
	int ch;	
	void (*fp)(void);

	fp=(void (*)(void))load_addr;		
	
	DownLoadEnd = 1;
	LoadLength = data_len;
	printf("\nReceived %x Bytes, END...\n", data_len);
	
	if(DownLoadOnly)
		return 0;
		
	puts("Boot Image? (y/n) ");
	while (1) {
		ch = getch();
		if (ch == 'y' || ch == 'Y') {
			putch(ch);			
			(*fp)();			
		}
		if (ch == 'n' || ch == 'N') {
			putch(ch);			
			break;
		}
	}		

	putch('\n');
	return 0;
}
