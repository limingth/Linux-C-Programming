#include <stdio.h>

void main(void)
 {
   char string[256];

   printf("Type in a string of characters and press Enter\n");
   gets(string);

   printf("The string was %s\n", string);
 }

