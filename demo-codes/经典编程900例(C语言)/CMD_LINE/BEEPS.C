#include <stdio.h>
#include <stdlib.h>

void main (int argc, char *argv[])
 {
   int count;  // The number of times to sound the speaker
   int i;      // The number of times the speaker has been sounded

   // Determine the number of times to ring the bell
   count = atoi(argv[1]);

   for (i = 0; i < count; i++)
     putchar(7);   // ASCII 7 sounds the speaker
 }

