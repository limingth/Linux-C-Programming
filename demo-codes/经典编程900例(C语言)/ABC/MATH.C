#include <stdio.h>

void main ()
 {
   int seconds_in_an_hour;
   
   float average;

   seconds_in_an_hour = 60 * 60;

   average = (5 + 10 + 15 + 20) / 4;

   printf("The number of seconds in an hour %d\n", 
     seconds_in_an_hour);

   printf("The average of 5, 10, 15, and 20 is %f\n",  
     average);

   printf("The number of seconds in 48 minutes is %d\n",
     seconds_in_an_hour - 12 * 60);
 }
