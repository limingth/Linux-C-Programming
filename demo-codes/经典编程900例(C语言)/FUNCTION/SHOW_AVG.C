#include <stdio.h>

float average_value(int a, int b, int c)
 {
   return ((a + b + c) / 3.0);
 }
         
void main(void)
 {
   printf("The average of 100, 133, and 155 is %f\n",
     average_value(100, 133, 155));
 }

