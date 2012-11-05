#include <stdio.h>
#include <ctype.h>

void main (void)
 {
   char string[] = "Jamsa's 1001 C & C++ Tips";

   int i;

   for (i = 0; string[i]; i++)
     putchar(toupper(string[i]));
   putchar('\n');

   for (i = 0; string[i]; i++)
     putchar(_toupper(string[i]));
   putchar('\n');
 }
