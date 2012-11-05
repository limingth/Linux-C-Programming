#include "console.h"
#include "hexput.h"

#define FIFO_SIZE  1024


struct fifo_struct {
	unsigned char buf[FIFO_SIZE];
	int start;
	int end;
};

struct hexhdr {
	unsigned short type;
	unsigned short count;
};


struct fifo_struct fifo;
static unsigned long exec_address;


static int fifo_init(struct fifo_struct *f)
{
	f->start = 0;
	f->end = 0;
	return 0;
}

static int fifo_write(struct fifo_struct *f, unsigned char *data, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		f->buf[f->end++] = data[i];
		if (f->end == FIFO_SIZE)
			f->end = 0;
	}

	return 0;
}

static int fifo_getc(struct fifo_struct *f, unsigned char *ch)
{
	if (f->start == f->end)
		return -1;
	*ch = f->buf[f->start++];
	if (f->start == FIFO_SIZE)
		f->start = 0;
	return 0;
}

static int fifo_isl(struct fifo_struct *f)
{
	int i;

	i = f->start;
	while (i != f->end) {
		if (f->buf[i] == 0x0d || f->buf[i] == 0x0a)
			break;
		i++;
		if (i == FIFO_SIZE)
			i = 0;
	}

	return (i != f->end);
}

static int fifo_readl(struct fifo_struct *f, unsigned char *data, int max_len)
{
	unsigned char ch;
	int len = 0;
	int i;

	if (!fifo_isl(f))
		return -1;

	while (1) {
		fifo_getc(f, &ch);
		if (ch == 0x0d)
			continue;
		if (ch == 0x0a)
			break;
		if (len <= max_len)
			data[len++] = ch;
	}

	return len;
}

static unsigned char hex_to_bin(unsigned short hex)
{
	unsigned short h, l;

	h = hex & 0x00ff;
	l = (hex >> 8) & 0x00ff;

	if (h >= '0' && h <= '9')
		h -= '0';
	else if (h >= 'A' && h <= 'F')
		h = (h - 'A') + 0x0a;

	if (l >= '0' && l <= '9')
		l -= '0';
	else if (l >= 'A' && l <= 'F')
		l = (l - 'A') + 0x0a;

	return (h << 4) + l;
}

static int hex_data(unsigned long addr, unsigned short *data, int len)
{
	unsigned char *p;
	int i;
	
	p = (unsigned char *)addr;
	for (i = 0; i < len; i++) {
		*p++ = hex_to_bin(*data++);
	}
}

static int hex_s0(unsigned char *str)
{
	return 0;
}

static int hex_mem(unsigned char *str, int n)
{
	struct hexhdr *hex_hdr;
	int len;
	unsigned long addr = 0;
	unsigned short *data;
	int i;

	hex_hdr = (struct hexhdr *)str;
	len = hex_to_bin(hex_hdr->count) - 1;

	data = (unsigned short *)(str + sizeof(struct hexhdr));
	for (i = 0; i < n; i++)
		addr = (addr << 8) + hex_to_bin(*data++);

	hex_data(addr, data, len);
	
	return 0;
}

static int hex_exec(unsigned char *str, int n)
{
	struct hexhdr *hex_hdr;
	unsigned long addr = 0;
	unsigned short *data;
	int i;

	hex_hdr = (struct hexhdr *)str;

	data = (unsigned short *)(str + sizeof(struct hexhdr));
	for (i = 0; i < n; i++)
		addr = (addr << 8) + hex_to_bin(*data++);

	exec_address = addr;

	return 0;
}

static int hex_proc(unsigned char *str)
{
	struct hexhdr *hex_hdr;

/*
	hex_hdr = (struct hexhdr *)str;
	switch (ntohs(hex_hdr->type)) {
	case 0x5330:
		hex_s0(str);
		break;
	case 0x5331:
		hex_mem(str, 2);
		break;
	case 0x5332:
		hex_mem(str, 3);
		break;
	case 0x5333:
		hex_mem(str, 4);
		break;
	case 0x5334:
	case 0x5335:
	case 0x5336:
	case 0x5337:
		hex_exec(str, 4);
		break;
	case 0x5338:
		hex_exec(str, 3);
		break;
	case 0x5339:
		hex_exec(str, 2);
		break;
	}

*/
	return 0;
}

int hex_put_begin(void)
{
	fifo_init(&fifo);
	exec_address = 0xffffffff;

	printf("\r\nStarting the TFTP download...\r\n");

	return 0;
}

int hex_put(unsigned char *data, int len)
{
	unsigned char str[256];
	int lenl;

	fifo_write(&fifo, data, len);
	while (1) {
		lenl = fifo_readl(&fifo, str, 256);
		if (lenl <= 0)
			break;
		str[lenl] = '\0';
		hex_proc(str);
	}

	return 0;
}

int hex_put_end(void)
{
	void (*fp)(void);

	printf("\r\nTFTP download completed...\r\n");
	if (exec_address != 0xffffffff) {
		printf("Transferring control to the downloaded code.\r\n\r\n");
		fp = (void (*)(void))(exec_address);
		(*fp)();
	}
	
	return 0;
}
