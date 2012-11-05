#include <stdio.h>
#include <time.h>

void main (void)
 {
   time_t current_time;

   time(&current_time);  // Get the time in seconds;

   printf("The current date and time: %s", 
     ctime(&current_time));
 }
