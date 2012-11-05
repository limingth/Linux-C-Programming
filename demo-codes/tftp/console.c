#include "types.h"
#include "console.h"
#include "utils.h"
#include "board.h"
#include <stdarg.h>

#define CONSOLE_OUTPUT            1

int console_init(void)
{
	outl(0x03, ULCON0);
	outl(0x09, UCON0);
	outl(0x500, UBRDIV0);		//19200
//	outl(0x1a0, UBRDIV0);		//57600

	return 0;
}

int console_write(int ch)
{
#ifdef CONSOLE_OUTPUT
	int i;
	if(ch=='\n')
	{
		while (!(inl(USTAT0) & 0x40));
		outl('\r', UTXBUF0);
		i = 1000;
		while(i--);
	}	
	while (!(inl(USTAT0) & 0x40));
	outl(ch, UTXBUF0);	
#endif

	return 0;
}

int console_read(void)
{
	while (!(inl(USTAT0) & 0x20));

	return (int)inl(URXBUF0);
}

int kbhit(void)
{
	return (inl(USTAT0) & 0x20);
}

int getch(void)
{
	return console_read();
}

int putch(int ch)
{
	return console_write(ch);
}

int puts(const char *s)
{
	int i;
	
	while (*s != 0) {
		putch(*s++);
		i = 1000;
		while(i--);
	}
	return 0;
}

char *gets(char *s, int n)
{
	char *p;
	int ch;

	p = s;
	while (1) {
		ch = getch();
		if (ch == KEY_ENTER)
			break;
		if (ch == KEY_BACKSPACE && p > s) {
			p--;
			putch(ch);
		} else if ((p - s) < (n - 1)) {
			*p++ = (char)ch;
			putch(ch);
		}
	}
	*p = '\0';

	return s;
}

unsigned long getul(unsigned long def)
{
	char buf[9];

	gets(buf, 9);
	if (buf[0] == '\0')
		return def;
	return strtoul(buf, NULL, 16);
}

void print_0nx(char ch2, unsigned long l)
{
	unsigned char ch;
	int i;

	ch2 = ch2 - '0';
	for (i = ch2 - 1; i >= 0; i--) {
		ch = (l >> (i * 4)) & 0x0f;
		if (ch < 10)
			putch(ch + '0');
		else
			putch(ch - 10 + 'a');
	}
}

void print_d(unsigned long l)
{
	unsigned long prod, t;
	int flag = 0;
	unsigned char ch;
	int i, j, k;

	for (i = 15; i >= 0; i--) {
		prod = 1;
		t = l;
		for (j = 0; j < i; j++) {
			prod = prod * 10;
			t = t / 10;
		}
		ch = t;
		l -= prod * t;

		if (ch == 0 && flag == 0)
			continue;

		if (ch < 10)
			putch(ch + '0');
		else
			putch('?');
			k = 1000;
			while(k--);

		flag = 1;
	}
}
/*
int printf(const char *s, ...)
{
	va_list ap;
	unsigned long arg;
	const char *str;
	char ch1, ch2, ch3;

	va_start(ap, s);
	while (*s != 0) {
		if (*s == '%') {
			s++;
			ch1 = *s++;
			if (ch1 == 's') {
				str = (const char *)va_arg(ap, unsigned char *);
				puts(str);
			} else if (ch1 == 'd') {
				arg = va_arg(ap, unsigned long);
				print_d(arg);
			} else {
				ch2 = *s++;
				ch3 = *s++;
				arg = va_arg(ap, unsigned long);
				print_0nx(ch2, arg);
			}
		} else
			putch(*s++);
	}
	va_end(ap);
	return 0;
}
*/
int get_select(int min, int max)
{
	int select;
	int ch;

	while (1) {
		ch = getch();
		if (ch >= min && ch <= max) {
			putch(ch);
			select = ch - min;
			break;
		}
		if (ch == KEY_ESC) {
			select = -1;
			break;
		}
	}

	return select;
}

#ifdef	__SDT_COMPILER
typedef char *__va_list[1];
#else
typedef int *__va_list[1];
#endif

int vsprintf(char * /*s*/, const char * /*format*/, __va_list /*arg*/);

int printf(const char *fmt, ...)
{
    va_list ap;
    char string[256];    

    va_start(ap, fmt);
    vsprintf(string, fmt, ap);
    puts(string);
    va_end(ap);
    
    return 0;
}