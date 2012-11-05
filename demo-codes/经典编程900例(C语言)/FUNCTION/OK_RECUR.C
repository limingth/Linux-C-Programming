#include <stdio.h>
#include <time.h>

int string_length(const char *str)
 {
   if (*str)
     return(1 + string_length(str+1));
   else
     return(0);
 }

void main(void)
 {
   long int counter;

   time_t start_time, end_time;

   time(&start_time);

   for (counter = 0; counter < 100000L; counter++)
     string_length("Jamsa's 1001 C/C++ Tips");
     
   time(&end_time);

   printf("Processing time %d\n", end_time - start_time);
 }

