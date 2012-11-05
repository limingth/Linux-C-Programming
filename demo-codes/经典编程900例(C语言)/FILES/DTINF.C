#include <stdio.h>
#include <dos.h>

void main (void)
 {
   struct date curr_date;
   struct time curr_time;

   FILE *input; 
   
   if ((input = fopen("DATETIME.OUT", "r")) == NULL)
     fprintf(stderr, "Error opening file DATETIME.OUT\n");
   else
     {
       fread(&curr_date, sizeof(curr_date), 1, input);
       fread(&curr_time, sizeof(curr_time), 1, input);
       fclose(input);

       printf("Date: %02d-%02d-%02d\n", curr_date.da_mon,
         curr_date.da_day, curr_date.da_year);
       printf("Time: %02d:%02d\n", curr_time.ti_hour, 
         curr_time.ti_min);
     }
 }
