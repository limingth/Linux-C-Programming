#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void main(void)
 {
   int i;

   srand(100);
   printf("Values from rand\n");
   for (i = 0; i < 5; i++)
     printf("%d ", rand());

   printf("\nSame 5 numbers\n");
   srand(100);
   for (i = 0; i < 5; i++)
     printf("%d ", rand());

   randomize();
   printf("\nDifferent 5 numbers\n");
   for (i = 0; i < 5; i++)
     printf("%d ", rand());
 }

