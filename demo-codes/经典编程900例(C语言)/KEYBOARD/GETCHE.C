#include <stdio.h>
#include <ctype.h>
#include <conio.h>

void main(void)
 {
   int letter;

   printf("Do you want to continue? (Y/N): ");
   do 
     {
       letter = getche();
       letter = toupper(letter);
     }
   while ((letter != 'Y') && (letter != 'N'));

   if (letter == 'Y')
     printf("\nYour response was Yes\n");
   else 
     printf("\nWhy not?\n");
 }
