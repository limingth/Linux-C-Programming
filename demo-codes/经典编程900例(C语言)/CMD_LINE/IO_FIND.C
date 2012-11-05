#include <stdio.h>
#include <string.h>

void main (int argc, char *argv[])
 {
   char string[256];

   while (fgets(string, sizeof(string), stdin))
     if (strstr(string, argv[1]))
       fputs(string, stdout);
 }

