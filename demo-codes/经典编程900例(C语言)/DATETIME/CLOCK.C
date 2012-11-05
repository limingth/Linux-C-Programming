#include <stdio.h>
#include <time.h>
#include <dos.h>    // Contains the delay prototype

void main (void)
 {
   clock_t processor_time;

   printf("Processor time consumed %ld\n", 
     clock() / (long) CLK_TCK);

   delay(2000);

   printf("Processor time consumed %ld\n", 
     (long) clock() / (long) CLK_TCK);

   delay(3000);

   printf("Processor time consumed %ld\n", 
     clock() / (long) CLK_TCK);
 }

