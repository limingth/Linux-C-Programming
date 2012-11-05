#include <stdio.h>
#include <time.h>

void main (void)
 {
   struct tm *gm_date;

   time_t seconds;

   time(&seconds);

   gm_date = gmtime(&seconds);

   printf("Current date: %d-%d-%d\n", gm_date->tm_mon+1, 
     gm_date->tm_mday, gm_date->tm_year);
   printf("Current time: %02d:%02d\n", gm_date->tm_hour,
     gm_date->tm_min);
 }

