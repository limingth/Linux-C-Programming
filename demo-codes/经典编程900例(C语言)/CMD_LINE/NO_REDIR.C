#include <stdio.h>
#include <dos.h>

void main (void)
  {
     union REGS inregs, outregs;

     // check the stdin handle first
     inregs.x.ax = 0x4400;
     inregs.x.bx = 0;      // stdin is handle 0
     intdos (&inregs, &outregs);

     if ((outregs.x.dx & 1) && (outregs.x.dx & 128))
       fprintf (stderr, "stdin has not been redirected\n");
     else
       fprintf (stderr, "stdin is redirected\n");                      

     // Now check stdout
     inregs.x.ax = 0x4400;
     inregs.x.bx = 1;      // stdout is handle 1
     intdos (&inregs, &outregs);

     if ((outregs.x.dx & 2) && (outregs.x.dx & 128))
       fprintf (stderr, "stdout has not been redirected\n");
     else
       fprintf (stderr, "stdout is redirected\n");                      
  }
