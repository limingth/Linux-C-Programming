#include <stdio.h>
#include <ctype.h>

void main (void)
 {
   int ascii_char;

   for (ascii_char = 0; ascii_char < 128; ascii_char++)
     if (isprint(ascii_char))
       printf("ASCII value %d setting (hex) %x ASCII %c\n",  
         ascii_char, _ctype[ascii_char], ascii_char);
     else
       printf("ASCII value %d setting (hex) %x ASCII %c\n",  
         ascii_char, _ctype[ascii_char], ascii_char);
 }

