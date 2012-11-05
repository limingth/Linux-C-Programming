#include <stdio.h>

void main ()
 {
   float accurate = 0.123456790987654321;
   double more_accurate = 0.1234567890987654321;

   printf("Value of float\t %21.19f\n", accurate);
   printf("Value of double\t %21.19f\n", more_accurate);
 }
