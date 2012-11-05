#include <stdio.h>

void main ()
 {
   int int_value = 5;
   float flt_value = 3.33;

   printf("Right justified %5d value\n", int_value);
   printf("Left justified %-5d value\n", int_value);
   
   printf("Right justified %7.2f value\n", flt_value);
   printf("Left justified %-7.2f value\n", flt_value);
 }
