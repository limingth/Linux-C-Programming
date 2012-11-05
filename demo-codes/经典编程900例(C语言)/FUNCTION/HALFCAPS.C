#include <stdio.h>
#include <string.h>

void main(void)
 {
   char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

   strupr(&alphabet[13]);

   printf(alphabet);
 }

