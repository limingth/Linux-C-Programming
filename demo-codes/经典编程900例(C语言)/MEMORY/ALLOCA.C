#include <stdio.h>
#include <malloc.h>

void some_function(size_t size)
 {
   int i;

   char *pointer;

   char stack_fix[1];
   stack_fix[0] = NULL;

   if ((pointer = alloca(size)) == NULL)
     printf("Error allocating %u bytes from the stack\n", size);
   else
     {
       for (i = 0; i < size; i++)    
         pointer[i] = i;
       printf("Allocatd and used a buffer of %u bytes\n", size);
     }
 }


void main(void)
 {
   some_function(1000);
   some_function(32000);
   some_function(65000);
 }


