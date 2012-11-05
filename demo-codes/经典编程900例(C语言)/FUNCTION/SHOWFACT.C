#include <stdio.h>

int factorial(int value)
 {
   printf("In factorial with the value %d\n", value);

   if (value == 1)
    {
      printf("Returning the value 1\n");
      return(1);
    }
   else
    { 
      printf("Returning %d * factorial(%d)\n", 
         value, value-1);
      return(value * factorial(value-1));
    }
 }

void main(void)
 {
   printf("The factorial of 4 is %d\n", factorial(4));
 }

