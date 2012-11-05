#include <stdio.h>
#include <dos.h>

void main (void)
 {
   struct SREGS segs;

   segread(&segs);

   printf("CS %X DS %X SS %X ES %X\n", segs.cs, 
     segs.ds, segs.ss, segs.es);
 }
