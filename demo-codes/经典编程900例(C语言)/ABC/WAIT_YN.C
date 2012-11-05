#include <stdio.h>
#include <ctype.h>
#include <conio.h>

void main()
 {
   char letter;  // Letter typed by the user

   printf("Do you want to continue? (Y/N): ");

   letter = getch();          // Get the letter  
   letter = toupper(letter);  // Convert letter to uppercase
   
   while ((letter != 'Y') && (letter != 'N'))
     {
       putch(7);                  // Beep the speaker
       letter = getch();          // Get the letter  
       letter = toupper(letter);  // Convert letter to uppercase
     }

   printf("\nYour response was %c\n", letter);
 }

