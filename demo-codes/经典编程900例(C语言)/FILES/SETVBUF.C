#include <stdio.h>
#include <dos.h>
#include <conio.h>

void main(void)
 { 
   char line[512];
   char *buffer;

   FILE *input;

   if ((input = fopen("\\AUTOEXEC.BAT", "r")) == NULL)
     printf("Error opening \\AUTOEXEC.BAT\n");
   else
    {
      if (setvbuf(input, buffer, _IOFBF, 8192))
        printf("Error changing file buffer\n");
      else
        while (fgets(line, sizeof(line), input))
          fputs(line, stdout);
        fclose(input);
    }
 }
