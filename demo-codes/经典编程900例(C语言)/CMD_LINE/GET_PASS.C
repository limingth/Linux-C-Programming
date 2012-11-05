#include <stdio.h>
#include <conio.h>
#include <string.h>

#define BACKSPACE 8
char *get_password(const char *prompt)
 {
   static char buffer[128];

   int i = 0;
   
   char letter = NULL;

   printf(prompt);

   while ((i < 127) && (letter != '\r'))
     {
       letter = getch();

       if (letter == BACKSPACE)
         {
           if (i > 0)
            {
              buffer[--i] = NULL;  // Erase previous *
              putchar(BACKSPACE);
              putchar(' ');
              putchar(BACKSPACE);
            }
           else
             putchar(7);  // BELL
         }
       else if (letter != '\r') 
         {
           buffer[i++] = letter;
           putchar('*');
         }
     }     
   buffer[i] = NULL;
   return (buffer);
 }


void main (void)
 {
   char *password;

   password = get_password("Enter Password: ");

   if (strcmp(password, "1001"))
     printf("\nPassword Incorrect\n");
   else
     printf("\nPassword OK\n");
 }
