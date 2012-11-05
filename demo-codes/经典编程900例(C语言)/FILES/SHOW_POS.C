#include <stdio.h>

void main(void)
 {
   FILE *input;

   int letter;

   if ((input = fopen("\\CONFIG.SYS", "r")) == NULL)
     printf("Error opening \\CONFIG.SYS\n");
   else
     { 
       printf("Current position is byte %d\n\n", ftell(input));

       // Read and write each character in the file
       while ((letter = fgetc(input)) != EOF)
         fputc(letter, stdout);
       
       printf("\nCurrent position is byte %d\n", ftell(input));
       
       fclose(input);     // Close the input file
     }
 }

