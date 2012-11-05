#include <stdio.h>
#include <stdlib.h>

void main (void)
 {
   char *entry;

   entry = getenv("PATH");

   if (*entry)
     printf("PATH=%s\n", entry);
   else
     printf("PATH is not defined\n");
 }

