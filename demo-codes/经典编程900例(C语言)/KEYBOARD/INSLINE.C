#include <conio.h>

void main(void)
 {
   int line;
  
   clrscr();

   for (line = 1; line < 25; line++)
    cprintf("This is line %d\r\n", line);

   cprintf("Press a key to Continue: ");
   getch();

   gotoxy(1, 12);

   insline();
   cprintf("This is new text!!!");
   gotoxy(1, 25);
 }


