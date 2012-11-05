#include <stdio.h>
#include <stdlib.h>

void main(void)
 { 
   FILE *fp;

   int word;

   if ((fp = fopen("DATA.DAT", "wb")) == NULL)
     {
       printf("Error opening DATA.DAT for output\n");
       exit(1);
     }
   else
     {
       for (word = 1; word <= 100; word++)
         putw(word, fp);
       fclose(fp);
     }

   if ((fp = fopen("DATA.DAT", "rb")) == NULL)
     {
       printf("Error opening DATA.DAT for input\n");
       exit(1);
     }
   else
     {
       do {
         word = getw(fp); 
         if ((word == EOF) && (feof(fp)))
           break;
         else
           printf("%d ", word);
       } while (1);
       fclose(fp);
     }
 }
