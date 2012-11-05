#include <stdio.h>

#define MIN(x, y) (((x) < (y)) ? (x): (y))
#define MAX(x, y) (((x) > (y)) ? (x): (y))

void main(void)
 {
   printf("Minimum of 3 and 5 is %d\n", MIN(3, 5));
   printf("Maximum of 3.4 and 3.1 is %f\n", MAX(3.4, 3.1));
   printf("Minimum of -100 and 1000 is %d\n", MIN(-100, 1000));
 }

  
