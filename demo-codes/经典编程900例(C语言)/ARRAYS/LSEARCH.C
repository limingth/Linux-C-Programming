#include <stdlib.h>
#include <stdio.h>

int compare_int(int *a, int *b)
 {
   return(*a - *b);
 }

int compare_float(float *a, float *b)
 {
   return((*a == *b) ? 0: 1);
 }


void main(void)
 {
   int int_values[10] = {1, 3, 2, 4, 5}; 
   int *int_ptr, int_value = 1001, elements = 5, i;

   printf("Array contents before search\n");
   for (i = 0; i < elements; i++)
     printf("%d ", int_values[i]);

   
   int_ptr = lsearch(&int_value, int_values, 
      &elements, sizeof(int), 
      (int (*) (const void *, const void *)) compare_int);

   printf("\nArray contents after search\n");
   for (i = 0; i < elements; i++)
     printf("%d ", int_values[i]);

 }

