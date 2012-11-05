#include <stdio.h>
#include <dos.h>

#define VIDEO 0xB800   // CGA base

void main(void)
 {
   FILE *fp;   
   int offset;
   char value;   

   if ((fp = fopen("SAVE_SCR.DAT", "rb")) == NULL)
     printf("Error opening file\n");
   else
    {
      for (offset = 0; offset < 8000; offset++)
       { 
         fscanf(fp, "%c", &value);
         pokeb(VIDEO, offset, value);
       }
      fclose(fp);
    }
 }
