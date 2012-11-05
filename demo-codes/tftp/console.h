#ifndef __CONSOLE_H
#define __CONSOLE_H

#define KEY_BACKSPACE  0x08
#define KEY_ENTER      0x0d
#define KEY_ESC        0x1b


int console_init(void);
int console_write(int ch);
int console_read(void);

int kbhit(void);
int getch(void);
int putch(int ch);
int puts(const char *s);
char *gets(char *s, int n);
unsigned long getul(unsigned long def);
int printf(const char *s, ...);
int get_select(int min, int max);

#endif /* __CONSOLE_H */
