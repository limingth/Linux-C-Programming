#include <stdio.h>

int streql(char *str1, char *str2)
 {
   while ((*str1 == *str2) && (*str1))
     {
       str1++;
       str2++;
     }

   return((*str1 == NULL) && (*str2 == NULL));
 }

void main(void) 
 {
   printf("Testing Abc and Abc %d\n", streql("Abc", "Abc"));  
   printf("Testing abc and Abc %d\n", streql("abc", "Abc"));  
   printf("Testing abcd and abc %d\n", streql("abcd", "abc"));  
 }
