#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <stdlib.h>
#include <dos.h>

void main(void)
 {
   char buffer[128];
   int row, column;    
   
   clrscr();
   cprintf("Jamsa's 1001 C/C++ Tips\r\n");
   gettext(1, 1, 23, 1, buffer);

   while (! kbhit())
    {
      clrscr();
      row = 1 + random(24);
      column = 1 + random(58);
      puttext(column, row, column+22, row, buffer);
      delay(2000);
    }
 }

