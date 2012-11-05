#include <stdio.h>
#include <math.h>

void main(void)
 { 
   double value;

   for (value = 0.0; value < 10.0; value += 0.1)
     printf("Value %f sqrt %f\n", value, sqrt(value));
 }

