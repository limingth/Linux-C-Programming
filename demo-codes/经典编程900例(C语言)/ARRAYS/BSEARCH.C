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
   int int_values[] = {1, 3, 2, 4, 5}; 
   float float_values[] = {1.1, 3.3, 2.2, 4.4, 5.5};  
   
   int *int_ptr, int_value = 2, elements = 5;
   float *float_ptr, float_value = 33.3;

   int_ptr = bsearch(&int_value, int_values, 
      elements, sizeof(int), 
      (int (*) (const void *, const void *)) compare_int);

   if (*int_ptr)
     printf("Value %d found\n", int_value);
   else 
     printf("Value %d not found\n", int_value);

   float_ptr = bsearch(&float_value, float_values, 
     elements, sizeof(float), 
     (int (*) (const void *, const void *)) compare_float);
   
   
   if (*float_ptr)
     printf("Value %3.1f found\n", float_value);
   else 
     printf("Value %3.1f not found\n", float_value);

 }

