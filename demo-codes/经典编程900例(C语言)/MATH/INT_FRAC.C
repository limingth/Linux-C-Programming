#include <stdio.h>
#include <math.h>

void main (void)
 {
   double value = 1.2345;
   double int_part;
   double fraction;

   fraction = modf(value, &int_part);

   printf("Value %f Integer part %f Fraction %f\n",
     value, int_part, fraction);
 }
