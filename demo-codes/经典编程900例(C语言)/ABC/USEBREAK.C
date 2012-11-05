#include <stdio.h>

void main()
 {
   int counter;

   for (counter = 1; counter <= 100; counter++)
    {
      if (counter == 50)
        break;

      printf("%d ", counter);
    }

   printf("\nNext loop\n");

   for (counter = 100; counter >= 1; counter--)
    {
      if (counter == 50)
        break;

      printf("%d ", counter);
    }
 }   
 
