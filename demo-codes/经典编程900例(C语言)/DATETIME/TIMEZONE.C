#include <stdio.h>
#include <time.h>

void main(void)
 {
   tzset();
   printf("Difference between local and GMT is %d hours\n",
     timezone / 3600);
 }

