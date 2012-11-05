#include <stdio.h>

char *strcpy(char *destination, const char *source) 
 {
   char *start = destination;

   while (*destination++ = *source++)
     ;

   return(start);
 }

void main(void)
 {
   char title[64]; 
   
   strcpy(title, "Jamsa's 1001 C/C++ Tips");
   printf(title);
 }

