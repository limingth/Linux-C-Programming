#include <stdio.h>
#include <dos.h>

extern unsigned _stklen = 8096;

void main(void)
 {
   printf("The current stack size %d bytes\n", _stklen);
 }
 
