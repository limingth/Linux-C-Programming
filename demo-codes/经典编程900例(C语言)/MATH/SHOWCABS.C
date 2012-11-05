#include <stdio.h>
#include <math.h>

void main (void)
 {
   struct complex complex_number;

   complex_number.x = 10;
   complex_number.y = 5;

   printf("Absolute value of 10,5 is %f\n", 
     cabs(complex_number));
 }
