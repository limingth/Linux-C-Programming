#include <stdio.h>
#include <string.h>

void main(void)
 {
   printf("Comparing Abc with Abc %d\n", 
     stricmp("Abc", "Abc"));
   printf("Comparing abc with Abc %d\n", 
     stricmp("abc", "Abc"));
   printf("Comparing 3 letters abcd with ABC %d\n", 
     strncmpi("abcd", "ABC", 3));
   printf("Comparing 5 letters abc with Abcd %d\n", 
     strncmpi("abc", "Abcd", 5));
 }   


