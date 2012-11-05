#include <stdio.h>
#include <dos.h>
#include <conio.h>

int alphanum = 0;
int counter = 0;

void interrupt far handler(void)
 {
   if (++counter == 273)  // 15 seconds   
     {
       alphanum = !alphanum;  // Toggle
       counter = 0;
     }
 }

void main(void)
 {
   int i;

   void interrupt far (*original_handler)();

   original_handler = _dos_getvect(0x1C);

   
   _disable();
   _dos_setvect(0x1c, handler);
   _enable();

   while (! kbhit())
     if (alphanum)
       for (i = 'A'; i <= 'Z'; i++)
          printf("%c\n", i);
     else
       for (i = 0; i <= 100; i++)
          printf("%d\n", i);

    _disable();
    _dos_setvect(0x1c, original_handler);
    _enable();
 }

