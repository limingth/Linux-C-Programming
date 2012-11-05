#include <stdio.h>

void main (void)
 {
   char string[256];

   int i;

   for (i = 0; i < 26; i++)
     string[i] = 'A' + i;

   string[10] = NULL;

   printf ("The string contains %s\n", string);
 }
