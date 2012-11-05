#include <stdio.h>

void main (void) 
 {
   char line[256];  // Line of redirected input

   long line_count = 0;

   while (fgets(line, sizeof(line), stdin))
     line_count++;

   printf("The number of redirected lines: %ld\n", line_count);
 }

