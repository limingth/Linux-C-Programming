#include <stdio.h>
#include <string.h>


void main(void)
 {
   printf("Comparing 3 letters Abc with Abc %d\n", 
     strncmp("Abc", "Abc", 3));
   printf("Comparing 3 letters abc with Abc %d\n", 
     strncmp("abc", "Abc", 3));
   printf("Comparing 3 letters abcd with abc %d\n", 
     strncmp("abcd", "abc", 3));
   printf("Comparing 5 letters Abc with Abcd %d\n", 
     strncmp("Abc", "Abcd", 5));
 }   


