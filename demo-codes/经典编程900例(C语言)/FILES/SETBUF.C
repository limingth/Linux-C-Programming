#include <stdio.h>
#include <dos.h>
#include <conio.h>

void main(void)
 { 
   char buffer[512];
   int letter;

   setbuf(stdout, buffer);

   puts("First line of output");
   puts("Second line of output");
   puts("Third line of output");
   
   delay(3000);

   printf("About to fill buffer\n");
   fflush(stdout);
 
   for (letter = 0; letter < 513; letter++) 
    { 
     putchar('A');
     delay(10);
    }
 }
