#include <stdio.h>

void main ()
 {
   int result;

   result = printf("Jamsa's 1001 C & C++ Tips!\n");

   if (result == EOF)
     fprintf(stderr, "Error within printf\n");
 }
