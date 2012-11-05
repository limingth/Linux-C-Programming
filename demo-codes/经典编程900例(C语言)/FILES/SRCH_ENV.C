#include <stdio.h>
#include <stdlib.h>

void main (int argc, char *argv[])
 {
   char path[128];
   
   _searchenv(argv[1], "LIB", path);

   if (path[0])
     printf("Pathname: %s\n", path); 
   else
     printf("File not found\n");
 }
