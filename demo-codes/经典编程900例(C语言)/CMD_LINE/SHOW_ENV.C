#include <stdio.h>

void main (int argc, char *argv[], char *env[])
 {
   int i;

   for (i = 0; env[i] != NULL; i++)
     printf ("env[%d] points to %s\n", i, env[i]);
 }

