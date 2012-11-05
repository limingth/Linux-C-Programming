#include <stdio.h>

void main ()
 {
   printf("File %s: Successfully reached line %d\n", 
     __FILE__, __LINE__);

   // Other statements here
   
#line 100 "FILENAME.C"

   printf("File %s: Successfully reached line %d\n", 
   __FILE__, __LINE__);
 }
