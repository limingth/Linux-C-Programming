#include <conio.h>

void main(void)
 {
  int color;

  for (color = 1; color < 16; color++)
   {
     textattr(color);
     cprintf("This is color %d\r\n", color);
   }

  textattr(128 + 15);
  cprintf("This is blinking\r\n");
 }

