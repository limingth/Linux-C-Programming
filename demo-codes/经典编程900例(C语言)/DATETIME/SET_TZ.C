#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(void)
 {
   putenv("TZ=PST8PDT");

   tzset();

   printf("Current time zone is %s\n", tzname[0]);

   if (tzname[1])
     printf("Daylight savings zone is %s\n", tzname[1]);
   else
     printf("Daylight savings zone is not defined\n");
 }

