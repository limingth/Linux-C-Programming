#include <stdio.h>

void main(void)
 {
   FILE *input, *output;

   int letter;

   if ((input = fopen("\\CONFIG.SYS", "r")) == NULL)
     printf("Error opening \\CONFIG.SYS\n");
   else if ((output = fopen("\\CONFIG.TST", "w")) == NULL)
     printf("Error opening \\CONFIG.TST\n");
   else
     { 
       // Read and write each character in the file
       while ((letter = fgetc(input)) != EOF)
         fputc(letter, output);

       fclose(input);     // Close the input file
       fclose(output);    // Close the output file
     }
 }

