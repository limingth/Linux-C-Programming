#include <stdio.h>
#include <ctype.h>

int strieql(char *str1, char *str2)
 {
   while ((toupper(*str1) == toupper(*str2)) && (*str1))
     {
       str1++;
       str2++;
     }

   return((*str1 == NULL) && (*str2 == NULL));
 }

void main(void) 
 {
   printf("Testing Abc and Abc %d\n", strieql("Abc", "Abc"));  
   printf("Testing abc and Abc %d\n", strieql("abc", "Abc"));  
   printf("Testing abcd and abc %d\n", strieql("abcd", "abc"));  
 }
