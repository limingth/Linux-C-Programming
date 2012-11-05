#include <stdio.h>
#include <dos.h>

void main(void)
 {
   union REGS inregs, outregs;

   inregs.h.ah = 0x30;
   inregs.h.al = 0;
   intdos(&inregs, &outregs);

   printf("Current version %d.%d\n", outregs.h.al, outregs.h.ah);
 }

