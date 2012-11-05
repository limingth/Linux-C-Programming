#include <stdio.h>

void main (void)
 {
   int positive = 32767;
   int negative = -32768;

   printf("%d + 1 is %d\n", positive, positive+1);
   printf("%d - 1 is %d\n", negative, negative-1);
 }
