#include <stdio.h>

void main(int argc, char **argv)
 {
   FILE *input, *output;

   char string[256];

   if ((input = fopen(argv[1], "r")) == NULL)
     printf("Error opening %s\n", argv[1]); 
   else if ((output = fopen(argv[2], "w")) == NULL)
     {
       printf("Error opening %s\n", argv[2]);
       fclose(input);
     }
   else 
     {
       while (fgets(string, sizeof(string), input))
         fputs(string, output);

       fclose(input);
       fclose(output);
     }
 }
