#include <stdio.h>

void main ()
 {
   int counter;

   for (counter = 1; counter <= 5; counter++)
    printf("%d ", counter);

   printf("\nStarting second loop\n");
   
   for (counter = 1; counter <= 10; counter++)
    printf("%d ", counter);

   printf("\nStarting third loop\n");

   for (counter = 100; counter <= 5; counter++)
    printf("%d ", counter);
 }
