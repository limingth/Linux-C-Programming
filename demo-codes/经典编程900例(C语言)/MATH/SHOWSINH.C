#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main(void)
 {
   double radians;
   double result;

   for (radians = 0.0; radians < 3.1; radians += 0.1)
     if (((result = sinh(radians)) == HUGE_VAL) && 
       (errno == ERANGE))
       printf("Overflow error\n");
     else
       printf("Sine of %f is %f\n", radians, result);
 }
