#include <stdio.h>

void no_change(const char *string)
 { 
   while (*string)
     *string++ = toupper(*string);
 }


 void main(void) 
  {
    char title[] = "Jamsa's 1001 C/C++ Tips";

    no_change(title);

    printf(title);
  }

