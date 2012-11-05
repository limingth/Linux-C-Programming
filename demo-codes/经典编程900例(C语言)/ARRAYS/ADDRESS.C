#include <stdio.h>

void main(void)
 {
   int count = 1;
   float salary = 40000.0;
   long distance = 1234567L;

   printf("Address of count is %x\n", &count);
   printf("Address of salary is %x\n", &salary);
   printf("Address of distance is %x\n", &distance);
 }

