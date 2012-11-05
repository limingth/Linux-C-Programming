#include <stdio.h>
#include <ctype.h>
#include <conio.h>

void main(void)
 {
   int letter;
   int done = 0;
   int uppercase_found = 0;

   do {
     letter = getch();

     if (islower(letter))
       putchar(letter);
     else
       {
         if (isupper(letter))
           {
             ungetch(letter);
             uppercase_found = 1;
             putchar('\n');
           }
         done = 1;
       }
   } while (! done);  

   if (uppercase_found)
     do {
       letter = getch();
       putchar(letter);
     } while (letter != '\r');
 }

