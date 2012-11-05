#include <stdio.h>
#include <time.h>

void main (void)
 {
   time_t start_time;
   time_t current_time;

   time(&start_time);

   printf("About to delay 5 seconds\n");

   do {
     time(&current_time);
   } while (difftime(current_time, start_time) < 5.0);

   printf("Done\n");
 }
