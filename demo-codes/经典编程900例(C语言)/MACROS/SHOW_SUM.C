#include <stdio.h>

#define SUM(x, y) ((x) + (y))

void main(void)
 {
   printf("Adding 3 + 5 = %d\n", SUM(3, 5));
   printf("Adding 3.4 + 3.1 = %f\n", SUM(3.4, 3.1));
   printf("Adding -100 + 1000 = %d\n", SUM(-100, 1000));
 }

  
