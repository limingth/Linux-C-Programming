#include <stdio.h>
#include <time.h>

void main (void)
 {
    time_t current_time;
    time_t start_time;

    printf("About to delay 5 seconds\n");

    time(&start_time);  // Get starting time in seconds

    do {
      time(&current_time);
    } while ((current_time - start_time) < 5);

    printf("Done\n");
 }



