#include <stdio.h>

void main (void)
 {
   char buffer[64];

   int counter;

   for (counter = 0; counter < 5; counter++)
     printf("Temporary filename %s\n", tmpnam(buffer));
 }
