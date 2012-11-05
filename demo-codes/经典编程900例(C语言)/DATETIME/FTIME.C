#include <stdio.h>
#include <time.h>
#include <sys\timeb.h>

void main(void)
 {
   struct timeb timezone;

   tzset();

   ftime(&timezone);

   printf("Seconds since 1 January 1970 (GMT) %ld\n",
     timezone.time);
   printf("Fractional seconds %d\n", timezone.millitm);
   printf("Hours difference between GMT and local zone %d\n",
     timezone.timezone / 60);
   if (timezone.dstflag)
     printf("Daylight savings time active\n");
   else
     printf("Daylight savings time inactive\n");
 }

