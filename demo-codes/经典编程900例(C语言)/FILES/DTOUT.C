#include <stdio.h>
#include <dos.h>
#include <io.h>
#include <sys\stat.h>

void main (void)
 {
   struct date curr_date;
   struct time curr_time;

   int handle;

   getdate(&curr_date);
   gettime(&curr_time);

   if ((handle = creat("DATETIME.OUT", S_IWRITE)) == -1)
     fprintf(stderr, "Error opening file DATETIME.OUT\n");
   else
     {
       write(handle, &curr_date, sizeof(curr_date));
       write(handle, &curr_time, sizeof(curr_time));
       close(handle);
     }
 }
