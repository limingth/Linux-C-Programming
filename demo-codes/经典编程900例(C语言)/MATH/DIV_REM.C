#include <stdio.h>
#include <stdlib.h>

void main (void)
 {
   div_t result;

   result = div(11, 3);

   printf("11 divided by 3 is %d Remainder %d\n",
     result.quot, result.rem);
 }
