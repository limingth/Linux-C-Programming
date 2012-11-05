#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   char *ptr;

   printf("Starting heap available %u\n", coreleft());
   
   
   ptr = malloc(1);  // Get pointer to current break value

   if (brk(ptr + 512) == 0)
   printf("Ending heap available %u\n", coreleft());
 }


