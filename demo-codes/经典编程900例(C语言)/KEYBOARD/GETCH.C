#include <stdio.h>
#include <conio.h>
#include <ctype.h>

void main(void)
 {
   int letter;

   printf("Type in a string of characters and press Enter\n");

   do { 
     letter = getch();
     letter = toupper(letter);
     putch(letter);
   } while (letter != '\r');
 }

    
   
