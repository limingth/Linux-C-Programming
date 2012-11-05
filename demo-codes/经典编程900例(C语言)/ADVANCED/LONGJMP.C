#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf location;   // Global variable

void function(void)
 {
   printf("About to longjmp\n");
   longjmp(location, 1);  // Return 1
 }

void main(void)
 {
     
   if (setjmp(location) != 0)  // Save the current location
     {
       printf("Returning from longjmp\n");
       exit(1);
     }
  
   function();
 }


