#include <stdio.h>
#include <dos.h>

void main (void)
 {
   unsigned drive_number;

   _dos_getdrive(&drive_number);

   printf("The current drive is %c\n", drive_number - 1 + 'A');
 }
