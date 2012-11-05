#include <stdio.h>
#include <dir.h>

void main (int argc, char *argv[])
 {
   char *path;

   if (path = searchpath(argv[1]))
     printf("Pathname: %s\n", path); 
   else
     printf("File not found\n");
 }
