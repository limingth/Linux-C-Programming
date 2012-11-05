#include <stdio.h>

int strlen(char str[])
 {
   int i = 0;

   while (str[i] != NULL)
     i++;

   return(i);
 }

void main(void)
 {
   printf("Length of ABC is %d\n", strlen("ABC"));
   printf("Length of 1001 C/C++ Tips is %d\n",
     strlen("1001 C/C++ Tips"));
   printf("Length of a NULL string is %d\n", strlen(""));
 }

