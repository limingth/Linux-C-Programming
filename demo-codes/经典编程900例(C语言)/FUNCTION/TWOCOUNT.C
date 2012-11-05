#include <stdio.h>

void beeper(int beep_count)
 {
   int count;

   for (count = 1; count <= beep_count; count++)
     putchar(7);
 }

void main(void)
 {
   int count;

   for (count = 1; count <= 3; count++)
     {
       printf("About to beep %d times\n", count);
       beeper(count);
     }
 }

