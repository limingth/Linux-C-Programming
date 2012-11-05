#include <stdio.h>
#include <math.h>

void main (void)
 {
   double value = 1.2345;

   double mantissa; 
   int exponent;

   mantissa = frexp(value, &exponent);

   printf("Mantissa %f Exponent %d Value %f\n", 
     mantissa, exponent, mantissa * pow(2.0, 1.0 * exponent));
 }
