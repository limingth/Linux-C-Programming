#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   char *one, *two, *three;

   if ((one = (char *) malloc(30000)) == NULL)
     printf("Error allocating array one\n");
   else if ((two = (char *) malloc(30000)) == NULL)
     printf("Error allocating array two\n");
   else if ((three = (char *) malloc(30000)) == NULL)
     printf("Error allocating array three\n");
   else
     printf("All arrays successfully allocated\n");
 }
