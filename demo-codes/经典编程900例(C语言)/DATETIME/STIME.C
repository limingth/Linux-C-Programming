#include <time.h>

void main(void)
 { 
   time_t seconds;

   time(&seconds);  // Get current time
   
   seconds += (time_t) 60 * 60 * 24;

   stime(&seconds);
 }

