#include <stdio.h>
#include <stdlib.h>

void main (int argc, char *argv[])
 {
   FILE *fp;

   char line[256]; 

   if (fp = fopen(argv[1], "r"))
     {
       while (fgets(line, sizeof(line), fp))
         {
           if (ferror(fp))
             {
               fprintf(stderr, "Error reading from %s\n", argv[1]);
               exit(1);
             }
           else 
             {
               fputs(line, stdout);
               if (ferror(fp))
                 {
                   fprintf(stderr, "Error writing to stdout\n");
                   exit(1);
                 }
             }
         }
     }
   else 
     printf("Error opening %s\n", argv[1]);
 }
