#include <stdio.h>
#include <dos.h>

void main (void)
 {
   unsigned drive_count;

   _dos_setdrive(3, &drive_count);
   printf("The number of available drives is %d\n", 
     drive_count);
 }
