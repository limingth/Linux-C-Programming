#include <stdio.h>

void main (void)
 {
   char string[256];  // String input by user

   int i;             // Index into the string

   printf("Type a string of characters and press Enter:\n");
   gets(string);

   // Display each string character until NULL is found
   for (i = 0; string[i] != NULL; i++)
     putchar(string[i]);
 
   printf("\nThe number of characters in the string is %d\n", i);
 }
