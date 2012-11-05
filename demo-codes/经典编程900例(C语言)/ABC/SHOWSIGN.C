#include <stdio.h>

void main ()
 {
   int neg_int = -5;
   int pos_int = 5;
   
   float neg_flt = -100.23;
   float pos_flt = 100.23;

   printf("The integer values are %+d and %+d\n",
     neg_int, pos_int);

   printf("The floating point values are %+f %+f\n",
     neg_flt, pos_flt);
 }

