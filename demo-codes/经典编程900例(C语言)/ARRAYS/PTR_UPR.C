#include <stdio.h>
#include <ctype.h>

char *string_uppercase(char *string)
 {
   char *starting_address;

   starting_address = string;

   while (*string)
     toupper(*string++);

   return(starting_address);
 }

void main(void)
 {
   char *title = "Jamsa's 1001 C/C++ Tips";
   char *string;

   string = string_uppercase(title);
   printf("%s\n", string);

   printf("%s\n", string_uppercase("Arrays and Pointers"));
 }
