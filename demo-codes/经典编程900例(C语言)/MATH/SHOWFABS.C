#include <stdio.h>
#include <math.h>

void main (void)
 {
   float value;

   for (value = -1.0; value <= 1.0; value += 0.1)
     printf("Value %f fabs %f\n", value, fabs(value));
 }
