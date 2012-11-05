#include <stdio.h>

void main(void)
 {
   struct Date {
     char month_name[64];
     int  month;
     int  day;
     int  year;
   } current_date = { "July", 7, 4, 1994 };

   int i;

   for (i = 0; current_date.month_name[i]; i++)
     putchar(current_date.month_name[i]);
 }

