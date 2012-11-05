#include <stdio.h>

void main(void)
 {
   int scores[5] = {80, 70, 90, 85, 80};
   int i;

   printf("Array Values\n");
 
   for (i = 0; i < 5; i++)
     printf("scores[%d] %d\n", i, scores[i]);
 }
