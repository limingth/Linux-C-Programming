#include <stdio.h>
#include <alloc.h>

void main(void)
 {  
   int *int_values;

   int i;

   if ((int_values = malloc(100 * sizeof(int))) == NULL)
     printf("Error allocating the array\n");
   else
     {
       for (i = 0; i < 100; i++)
         int_values[i] = i;

       for (i = 0; i < 100; i++)
         printf("%d ", int_values[i]);

       free(int_values);
     }
 }

