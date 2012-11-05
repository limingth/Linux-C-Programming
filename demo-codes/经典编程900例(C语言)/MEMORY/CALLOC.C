#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   char *string;
   int *int_values;
   float *float_values;

   if ((string = (char *) calloc(50, sizeof(char))))
     printf("Successfully allocated a 50 byte string\n");
   else
     printf("Error allocating string\n");

   if ((int_values = (int *) calloc(100, sizeof(int))) != NULL)
     printf("Successfully allocated int_values[100]\n");
   else 
     printf("Error allocating int_values[100]\n");

   if ((float_values = (float *) calloc(25, sizeof(float))) != NULL)
     printf("Successfully allocated float_values[25]\n");
   else
     printf("Error allocating float_values[25]\n");
 }

