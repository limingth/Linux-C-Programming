#include <stdio.h>
#include <mem.h>

void main(void)
 {
   float values[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
   float empty[5];

   int i;

   memmove(empty, values, sizeof(values));

   for (i = 0; i < 5; i++)
     printf("%3.1f ", empty[i]);
 }
