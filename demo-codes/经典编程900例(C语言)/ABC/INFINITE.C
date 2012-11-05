#include <stdio.h>

void main ()
 {
   int i;
   int result = 0;
   int value = 1;

   for (i = 0; i < 100; i++)
    {
      printf("%d ", i);
      result = value * --i;   
    }
 
   printf("Result %d\n", result);
 }
