#include <stdio.h>
#include <math.h>

void main(void)
 {
   double radians;

   for (radians = 0.0; radians < 3.1; radians += 0.1)
     printf("Sine of %f is %f\n", radians, sin(radians));
 }
