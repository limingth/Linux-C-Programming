#include <stdio.h>
#include <alloc.h>

void main (void)
 {
#if defined(__SMALL__)
   unsigned result;
#else
   long result;
#endif

   result = coreleft();

   printf("The amount of available memory is %dKb\n",
     result / 1024);
 }
