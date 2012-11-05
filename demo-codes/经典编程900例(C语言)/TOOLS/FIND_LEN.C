#include <stdio.h>

int string_length(char *);

void main(void)
 {
   char *title= "Jamsa's 1001 C/C++ Tips";
   char *section = "Tools";

   printf("Length of %s is %d\n", title, string_length(title));
   printf("Length of %s is %d\n", section, string_length(section));
 }

