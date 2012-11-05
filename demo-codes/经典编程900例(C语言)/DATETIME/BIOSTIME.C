#include <stdio.h>
#include <bios.h>

void main (void)
 {
   long ticks;

   ticks = biostime(0, ticks);

   printf("Ticks since midnight %ld\n", ticks);

   _bios_timeofday(_TIME_GETCLOCK, &ticks);

   printf("Seconds since midnight %f\n", ticks / 18.2);
 }
