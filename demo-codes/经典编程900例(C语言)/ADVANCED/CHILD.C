#include <stdlib.h>
#include <stdio.h>

void main(int argc, char *argv[], char *env[])
 {
   printf("Command line\n");
   while (*argv)
     puts(*argv++);

   printf("Environment entries\n");
   while (*env)
     puts(*env++);
 }

