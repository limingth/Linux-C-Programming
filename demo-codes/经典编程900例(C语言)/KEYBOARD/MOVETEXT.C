#include <conio.h>

void main(void)
 {
   int i;

   clrscr();
   for (i = 1; i <= 5; i++)
     cprintf("This is line %d\r\n", i);

   cprintf("Press any key\n\r");
   getch();   

   movetext(1, 1, 30, 6, 45, 18);
   gotoxy(1, 24);
 }

