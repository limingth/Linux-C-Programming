#include <stdio.h>

int str_index(const char *string, int letter)
 {
   char *original = string;

   while ((*string != letter) && (*string))
     string++;

   return(string - original);
  }


 void main(void)
  {
    printf("Location of C is %d\n", str_index("1001 C/C++", 'C'));

    printf("Location of x is %d\n", str_index("1001 C/C++", 'x'));
  }

