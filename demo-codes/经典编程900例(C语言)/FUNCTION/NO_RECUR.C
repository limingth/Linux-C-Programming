#include <stdio.h>
#include <time.h>

int string_length(const char *str)
 {
   int length = 0;
   
   while (*str++)
     length++;

   return(length);
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

