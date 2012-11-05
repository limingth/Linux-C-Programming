#include <stdio.h>
#include <time.h>

float add_em(long int a, float b)
 {
    float result;

    result = a + b;

    return(result);
 }

 void main(void)
  {
    long int i;
    float result = 0;
    time_t start_time, stop_time;

    printf("Working...\n");
    time(&start_time);

    for (i = 1; i <= 100000L; i++)
      result += i;

    time(&stop_time);

    printf("Using loop %d seconds\n", stop_time - start_time);

    printf("Working...\n");
    time(&start_time);

    for (i = 1; i <= 100000L; i++)
      result = add_em(i, result);

    time(&stop_time);

    printf("Using function %d seconds\n", stop_time - start_time);
 }
