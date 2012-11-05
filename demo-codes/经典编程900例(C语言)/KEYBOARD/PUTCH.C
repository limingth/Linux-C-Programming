#include <stdio.h>
#include <conio.h>
#include <time.h>


void main(void)
 {
   int letter;
   int count;

   time_t start_time, stop_time;
   
   time(&start_time);
   for (count = 0; count < 1000; count++)
    for (letter = 'A'; letter <= 'Z'; letter++)
     putchar(letter);
   time(&stop_time);

   printf("\n\nTime required for putchar %d seconds\n", 
     stop_time-start_time);
   printf("Press any key...\n");
   getch();

   time(&start_time);
   for (count = 0; count < 1000; count++)
    for (letter = 'A'; letter <= 'Z'; letter++)
     putch(letter);
   time(&stop_time);

   printf("\n\nTime required for putch %d seconds\n", 
     stop_time-start_time);
 }

