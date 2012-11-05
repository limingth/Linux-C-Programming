#include <stdio.h>
#include <dos.h>

void main (void)
 {
   struct date desired_date;

   desired_date.da_mon = 12;
   desired_date.da_day = 8;
   desired_date.da_year = 1993;

   setdate(&desired_date);
 }
