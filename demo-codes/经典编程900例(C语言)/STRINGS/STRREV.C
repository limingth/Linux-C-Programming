#include <stdio.h>

char *strrev(char *string)
 {
   char *original = string;
   char *forward = string;

   char temp;

   while (*string)
     string++;

   while (forward < string) 
    {
      temp = *(--string);
      *string = *forward; 
      *forward++ = temp;
    }
  return(original);
 }

void main(void)
 {
   printf(strrev("A"));
   printf("\n");

   printf(strrev(""));
   printf("\n");

   printf(strrev("ABC"));
   printf("\n");

   printf(strrev("AABBCCDDEE"));
 }
