#include <stdio.h>
#include <math.h>

void main (void)
 {
   int power;

   for (power = -2; power <= 2; power++)
     printf("10 raised to %d is %f\n", power,
       pow(10.0, power));
 }
