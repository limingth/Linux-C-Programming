#include <stdio.h>

long sum_array(int array[], int elements)
 {
   long sum = 0;

   int i;

   for (i = 0; i < elements; i++)
     sum += array[i];

   return(sum);
 }


void main(void)
 {
   int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   int b[2][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                   {11, 12, 13, 14, 15, 16, 17, 18, 19, 20}};
   int c[3][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                   {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
                   {21, 22, 23, 24, 25, 26, 27, 28, 29, 30}};

   printf("Sum of first array elements %d\n", sum_array(a, 10));
   printf("Sum of second array elements %d\n", sum_array(b, 20));
   printf("Sum of third array elements %d\n", sum_array(c, 30));
 }
