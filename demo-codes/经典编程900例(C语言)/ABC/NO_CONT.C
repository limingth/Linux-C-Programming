#include <stdio.h>

void main()
 {
   int counter;

   printf("\nEven values\n");
   for (counter = 1; counter <= 100; counter++)
     {
       if (!(counter % 2))  // Even
         printf("%d ", counter);
     }

   printf("\nOdd values\n");
   counter = 0;
   while (counter <= 100) 
     {
       counter++;

       if (counter % 2) // Odd 
         printf("%d ", counter);
     }
 }

