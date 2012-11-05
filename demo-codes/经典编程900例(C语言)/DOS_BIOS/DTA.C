#include <stdio.h>
#include <dos.h>
#include <malloc.h>

void main(void)
 {
   char far *dta;

   dta = getdta();

   printf("Current DTA is %lX\n", dta);
 
   if (MK_FP(_psp, 0x80) == dta)
     printf("DTA is at same location as command line\n");

   dta = _fmalloc(128);
   setdta(dta);

   printf("New DTA is %lX\n", getdta());
 }

