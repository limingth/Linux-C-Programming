#include <stdio.h>

void main(void)
 { 
   int value = 1001;

   if (value > 1000)
     {
       int value = 1;

       printf("Inner value is %d\n", value);
     }

   printf("Outer value is %d\n", value); 
 }
