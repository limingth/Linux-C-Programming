#include <stdio.h>
#include <stdlib.h>

void main (void)
 {
   if (putenv("BOOK=Jamsa's 1001 C & C++ Tips"))
     printf("Error writing to environment\n");
   else
     {
       int i;

       for (i = 0; environ[i]; ++i)
         printf("%s\n", environ[i]);
     }
 }
