#include <stdio.h>
#include <string.h>

void main (void)  
 {
   char line[255];  // Line of text read 

   while (fgets(line, sizeof(line), stdin))
     {
       fputs(line, stdout);
       strcat(line, "\r");
       fputs(line, stdprn);
     }
 }

