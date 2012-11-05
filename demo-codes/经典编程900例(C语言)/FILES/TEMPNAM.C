#include <stdio.h>

void main (void)
 {
   char buffer[64];

   int counter;

   printf("Temporary filename %s\n", tempnam(buffer, "1001"));
 }
