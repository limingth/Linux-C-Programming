#include <conio.h>

void main(void)
 {
   int a, b, c;

   cprintf("Type 3 integer values and press Enter\r\n");
   cscanf("%d %d %d", &a, &b, &c);
   cprintf("The values entered were %d %d %d\r\n", a, b, c);
 }
