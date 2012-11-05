#include <stdio.h>
#include <dos.h>

void main (void)
 {
   struct time curr_time;

   gettime(&curr_time);

   printf("Current time %02d:%02d:%02d.%02d\n", curr_time.ti_hour,
    curr_time.ti_min, curr_time.ti_sec, curr_time.ti_hund);
 }
