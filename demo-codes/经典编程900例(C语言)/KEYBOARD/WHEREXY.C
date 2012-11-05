#include <conio.h>

void main(void)
 {
   int row, column;

   clrscr();

   cprintf("This is line 1\r\n");
   cprintf("Line 2 is a little longer\r\n");
   cprintf("This is the last line");

   row = wherey();
   column = wherex();

   cprintf("\r\nThe cursor position was row %d column %d\n",
     row, column);
 }

