#include <stdio.h>

void main (void)
 {
   long character_count = 0; 

   getchar();

   while (! feof(stdin))
     {
       getchar();
       character_count++;
     }

   printf("The number of redirected characters is %ld\n", 
     character_count);
 }

