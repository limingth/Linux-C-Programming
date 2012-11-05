#include <stdio.h>

void main(void)
 {
   int letter;

   do {
     letter = getchar();
     putchar(letter);
   } while (letter != '\n');
 }

