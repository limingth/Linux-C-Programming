#include <stdio.h>
#include <string.h>

char *strset(char *string, int letter)
 {
   char *original = string;

   while (*string)
     *string++ = letter;
 
   return(original);
 }

void main(void)
 {
   char name[] = "22222";

   printf(strset(name, '1'));
 }

   
 
