#include <conio.h>

void main(void)
 {
   clrscr();

   highvideo();
   cprintf("This text is high video\r\n");

   lowvideo();
   cprintf("This text is low video\r\n");

   normvideo();
   cprintf("This text is normal video\r\n");
 }

