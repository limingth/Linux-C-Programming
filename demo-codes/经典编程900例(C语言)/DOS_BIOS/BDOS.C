#include <stdio.h>
#include <dos.h>

void main(void)
 {
   int drive;

   drive = bdos(0x19, 0, 0);

   printf("Current drive is %c\n", 'A' + drive);
 }

