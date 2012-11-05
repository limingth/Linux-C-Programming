#include <stdio.h>
#include <dos.h>

#define VIDEO 0xB800   // CGA base

void main(void)
 {
   FILE *fp;   
   int offset;
   
   if ((fp = fopen("SAVE_SCR.DAT", "wb")) == NULL)
     printf("Error opening file\n");
   else
    {
      for (offset = 0; offset < 8000; offset++)
        fprintf(fp, "%c", peekb(VIDEO, offset));
      fclose(fp);
    }
 }
