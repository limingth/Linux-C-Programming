#include <stdlib.h>
#include <stdio.h>

int compare_int(int *a, int *b)
 {
   return(*a - *b);
 }

int compare_float(float *a, float *b)
 {
   if (*a < *b)
     return(-1);
   else if (*a == *b)
     return(0);
   else
     return(1);
 }


void main(void)
 {
   int int_values[] = {51, 23, 2, 44, 45}; 
   float float_values[] = {21.1, 13.3, 22.2, 34.4, 15.5};  
   
   int elements = 5, i;
   
   qsort(int_values, elements, sizeof(int), 
      (int (*) (const void *, const void *)) compare_int);

   for (i = 0; i < elements; i++)
     printf("%d ", int_values[i]);

   putchar('\n');

   qsort(float_values, elements, sizeof(float), 
     (int (*) (const void *, const void *)) compare_float);
   
   for (i = 0; i < elements; i++)
     printf("%4.1f ", float_values[i]);
 }

