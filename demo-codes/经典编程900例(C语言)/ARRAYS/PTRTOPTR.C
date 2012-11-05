#include <stdio.h>

int what_is_the_value(int ***ptr)
 {
   return(***ptr);
 }

void main(void)
 {
   int *level_1, **level_2, ***level_3, value = 1001;

   level_1 = &value;
   level_2 = &level_1;
   level_3 = &level_2;

   printf("The value is %d\n", what_is_the_value(level_3));
 }

