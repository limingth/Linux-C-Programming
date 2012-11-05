#include <stdio.h>

int factorial(int value)
 {
   int result = 1;
   int counter;

   for (counter = 2; counter <= value; counter++) 
     result *= counter;

   return(result);
 }

void main(void)
 {
   int i;

   for (i = 1; i <= 5; i++)
     printf("Factorial of %d is %d\n", i, factorial(i));
 }
