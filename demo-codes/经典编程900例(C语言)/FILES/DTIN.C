#include <stdio.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>

void main (void)
 {
   struct date curr_date;
   struct time curr_time;

   int handle;

   if ((handle = open("DATETIME.OUT", O_RDONLY)) == -1)
     fprintf(stderr, "Error opening file DATETIME.OUT\n");
   else
     {
       read(handle, &curr_date, sizeof(curr_date));
       read(handle, &curr_time, sizeof(curr_time));
       close(handle);

       printf("Date: %02d-%02d-%02d\n", curr_date.da_mon,
         curr_date.da_day, curr_date.da_year);
       printf("Time: %02d:%02d\n", curr_time.ti_hour, 
         curr_time.ti_min);
     }
 }
