#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>

void main()
 {
   char letter;
   
   do {
     printf("A Display directory listing\n");
     printf("B Display disk information\n");
     printf("C Change system date\n");
     printf("Q Quit\n");
     printf("Choice: ");
     
     letter = getch();     
     letter = toupper(letter);

     if (letter == 'A')
       system("DIR");
     else if (letter == 'B')
       system("CHKDSK");
     else if (letter == 'C')
       system("DATE");
    }
   while (letter != 'Q');
 }

