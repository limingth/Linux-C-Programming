#include <stdio.h>
#include <dos.h>

void main(void)
 {
   union REGS inregs, outregs;

   inregs.x.ax = 0x3000;
   intdos(&inregs, &outregs);

   printf("Current version %d.%d\n", outregs.x.ax & 0xFF,
     outregs.x.ax >> 8);
 }

