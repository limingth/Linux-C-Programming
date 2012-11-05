#include <stdio.h>
#include <mem.h>

void main(void)
 {
   char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   char target[27];
   char *result;

   result = memccpy(target, alphabet, 'K', sizeof(alphabet));
   
   if (result)
     *result = NULL;

   printf(target);
 }

