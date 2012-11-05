#include <stdio.h>

int strr_index(const char *string, int letter)
 {
   char *original = string;
   char *ptr = NULL;

   while (*string)
    {
     if (*string == letter)
       ptr = string;

     string++;
    }

   return((*ptr) ? ptr-original: string-original);
  }


 void main(void)
  {
    printf("Location of C is %d\n", strr_index("1001 C/C++", 'C'));

    printf("Location of x is %d\n", strr_index("1001 C/C++", 'x'));
  }

