#include <stdio.h>
#include <time.h>

void main(void)
 {
   char buffer[128];

   struct tm *datetime;
   time_t current_time;

   tzset();

   time(&current_time);
   datetime = localtime(&current_time);

   strftime(buffer, sizeof(buffer), "%x %X", datetime);
   printf("Using %%x %%X: %s\n", buffer);
   
   strftime(buffer, sizeof(buffer), "%A %B %m, %Y", datetime);
   printf("Using %%A %%B %%m %%Y: %s\n", buffer);
 
   strftime(buffer, sizeof(buffer), "%I:%M%p", datetime);
   printf("Using %%I:%%M%%p: %s\n", buffer);
 }



