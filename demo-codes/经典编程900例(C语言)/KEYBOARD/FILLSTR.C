#include <stdio.h>

void main(void)
 {
   char string[128];

   int index = 0;
   int letter;

   printf("Type in a string and press Enter\n");
   while ((letter = getchar()) != '\n')
     string[index++] = letter;

   string[index] = NULL;

   printf("The string was: %s\n", string);
 }

   
