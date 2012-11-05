#include <stdio.h>
#include <dos.h>

void main(void)
 {
   int i;

   for (i = 0; i <= 255; i++)
     printf("Interrupt: %x Vector: %lx\n", 
       i, _dos_getvect(i));
 }

