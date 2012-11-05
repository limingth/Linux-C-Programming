#include <dos.h>
#include <conio.h>

void main(void)
 {
   unsigned frequency;

   do {
     for (frequency = 500; frequency <= 1000; frequency += 50)
      { 
       sound(frequency);
       delay(50);
      }
     for (frequency = 1000; frequency >= 500; frequency -= 50)
      { 
       sound(frequency);
       delay(50);
      }
   } while (! kbhit());

   nosound();
 }
