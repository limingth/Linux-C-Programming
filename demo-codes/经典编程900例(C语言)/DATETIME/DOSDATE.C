#include <stdio.h>
#include <dos.h>

void main (void)
 {
   struct date curr_date;

   getdate(&curr_date);

   printf("Current date: %d-%d-%d\n", curr_date.da_mon,
     curr_date.da_day, curr_date.da_year); 
 }
