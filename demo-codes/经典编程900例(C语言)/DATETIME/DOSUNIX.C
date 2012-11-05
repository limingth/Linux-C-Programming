#include <stdio.h>
#include <dos.h>
#include <time.h>

void main (void)
 {
   struct time dostime;
   struct date dosdate;

   time_t unix_format;
   struct tm *local;

   getdate(&dosdate);
   gettime(&dostime);

   unix_format = dostounix(&dosdate, &dostime);
   local = localtime(&unix_format);
   printf("UNIX time: %s\n", asctime(local));
 }
