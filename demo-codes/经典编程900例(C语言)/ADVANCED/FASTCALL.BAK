#include <stdio.h>
#include <time.h>

int _fastcall add_fast(int a, int b)
 {
   return(a + b);
 }

int add_slow(int a, int b)
 { 
   return(a + b);
 }

void main(void)
 { 
   unsigned long int i, result;

   clock_t start_time, stop_time;

   printf("Processing...\n");
   start_time = clock();

   for (i = 0; i < 2000000L; i++)
     result = add_fast(i, -i);

   stop_time = clock();
   printf("Processing time for fast call %d ticks\n", 
     stop_time - start_time);
   
   start_time = clock();

   for (i = 0; i < 2000000L; i++)
     result = add_slow(i, -i);

   stop_time = clock();
   printf("Processing time for normal call %d ticks\n", 
     stop_time - start_time);
 }
