#include <stdio.h>

int i_cube(int value)
 {
   return(value * value * value);
 }

void main(void)
 {
   printf("The cube of 3 is %d\n", i_cube(3));
   printf("The cube of 5 is %d\n", i_cube(5));
   printf("The cube of 7 is %d\n", i_cube(7));
 }
