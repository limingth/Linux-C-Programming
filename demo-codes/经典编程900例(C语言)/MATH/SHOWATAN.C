#include <stdio.h>
#include <math.h>

void main (void)
 {
   double radians;

   for (radians = -0.5; radians <= 0.5; radians += 0.2)
     printf("%f %f\n", radians, atan(radians));
 }

