#include <stdio.h>
#include <ctype.h>

void no_change(const char *string)
 { 
   char *alias = string;

   while (*alias)
     *alias++ = toupper(*alias);
 }


 void main(void) 
  {
    char title[] = "Jamsa's 1001 C/C++ Tips";

    no_change(title);

    printf(title);
  }

