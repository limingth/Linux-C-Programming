#include <conio.h>

void main(void)
 {
   int i, j;

   window(1, 1, 40, 12);

   for (i = 0; i < 15; i++)
    {
      for (j = 0; j < 50; j++)
       cprintf("%d", j);
      cprintf("\r\n");
    }
 }


