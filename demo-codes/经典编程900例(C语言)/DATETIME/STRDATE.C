#include <stdio.h>
#include <time.h>

void main (void)
 {
   char date[9];

   _strdate(date);

   printf("The current date is %s\n", date);
 }
