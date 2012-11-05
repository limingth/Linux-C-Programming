#include <stdio.h>
#include <time.h>

void main(void)
 {
   time_t seconds;

   struct tm time_fields;

   time_fields.tm_mday = 4;
   time_fields.tm_mon = 7;
   time_fields.tm_year = 94;
   time_fields.tm_hour = 0;
   time_fields.tm_min = 0;
   time_fields.tm_sec = 0;

   seconds = mktime(&time_fields);

   printf("The number of seconds between 7-4-94 and 1-1-70 is %ld\n",
     seconds);
 }

