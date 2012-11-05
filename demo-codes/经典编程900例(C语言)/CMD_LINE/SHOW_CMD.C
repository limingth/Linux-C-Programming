#include <stdio.h>

void main (int argc, char *argv[])
 {
   int i;

   for (i = 0; i < argc; ++i)
     printf ("argv[%d] points to %s\n", i, argv[i]);
 }

