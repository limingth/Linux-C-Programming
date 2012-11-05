#include <conio.h>

void main(void)
 {
   int color;

   for (color = 0; color < 8; color++)
    { 
     textbackground(color);
     cprintf("This is color %d\r\n", color);
     cprintf("Press any key to continue\r\n");
     getch();
    }
 }

