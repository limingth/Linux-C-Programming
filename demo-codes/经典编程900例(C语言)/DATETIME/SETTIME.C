#include <stdio.h>
#include <dos.h>

void main (void)
 {
   struct time desired_time;

   desired_time.ti_hour = 12;
   desired_time.ti_min = 30;

   settime(&desired_time);
 }


