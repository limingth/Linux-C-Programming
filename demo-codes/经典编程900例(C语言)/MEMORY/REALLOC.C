#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   char *string, *new_string;
    
   if ((string = (char *) malloc(100)))
     {
       printf("Successfully allocated a 100 byte string\n");
       if ((new_string = (char *) realloc(string, 1000)))
         printf("String size increased to 1000\n");
       else
         printf("Error reallocating the string\n");
     }
   else
     printf("Error allocating the 100 byte string\n");
 }


