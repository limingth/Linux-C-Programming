#include <stdio.h>

void main ()
 { 
   int value = 1;
   
   printf("Using postfix %d\n", value++); 
   printf("Value after increment %d\n", value);

   value = 1;

   printf("Using prefix %d\n", ++value); 
   printf("Value after increment %d\n", value);
 }
