#include <stdio.h>

void main (int argc, char **argv, char **env)
 { 
   while (*env)
     printf("%s\n", *env++);
 }

