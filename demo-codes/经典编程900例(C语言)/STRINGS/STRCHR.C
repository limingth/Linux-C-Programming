#include <stdio.h>
#include <string.h>

void main(void)
 {
   char title[64] = "1001 C/C++ Tips!";
   char *ptr;

   if (ptr = strchr(title, 'C'))
     printf("First occurrence of C is at offset %d\n",
       ptr - title);
   else
     printf("Character not found\n");
 }
