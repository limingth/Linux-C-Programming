#include <stdio.h>
#include <string.h>

void main(void)
 {
   printf("Comparing Abc with Abc %d\n", strcmp("Abc", "Abc"));
   printf("Comparing abc with Abc %d\n", strcmp("abc", "Abc"));
   printf("Comparing abcd with abc %d\n", strcmp("abcd", "abc"));
   printf("Comparing Abc with Abcd %d\n", strcmp("Abc", "Abcd"));
 }   


