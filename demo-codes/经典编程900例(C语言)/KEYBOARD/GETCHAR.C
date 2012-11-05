#include <stdio.h>
#include <ctype.h>

void main(void)
 {
   int letter;
  
   printf("Type Y or N to continue and press Enter\n");

   do { 
     letter = toupper(getchar());
   } while ((letter != 'Y') && (letter != 'N'));
 
   printf("You typed %c\n", ((letter == 'Y') ? 'Y': 'N'));
 }

