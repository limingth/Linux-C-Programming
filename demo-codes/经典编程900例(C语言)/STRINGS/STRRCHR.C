#include <stdio.h>
#include <string.h>

char *strrchr(const char *string, int letter)
 {
   char *ptr = NULL;

   while (*string)
     {
       if (*string == letter)
         ptr = string;
       string++;
     }
   return(ptr);
 }

void main(void)
 {
   char title[64] = "1001 C/C++ Tips!";
   char *ptr;

   if (ptr = strrchr(title, 'C'))
     printf("Rightmost occurrence of C is at offset %d\n",
       ptr - title);
   else
     printf("Character not found\n");
 }
