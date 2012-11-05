#include <stdio.h>

void main(void)
 {
   int int_values[] = {51, 23, 2, 44, 45}; 
   float float_values[] = {21.1, 13.3, 22.2, 34.4, 15.5};  
 
   printf("Number of elements in int_values %d\n",
     sizeof(int_values) / sizeof(int_values[0]));

   printf("Number of elements in float_values %d\n",
     sizeof(float_values) / sizeof(float_values[0]));

 }

