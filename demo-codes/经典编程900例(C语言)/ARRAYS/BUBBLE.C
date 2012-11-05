#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int array[], int size)
 {
   int temp, i, j;

   for (i = 0; i < size; i++) 
    for (j = 0; j < size; j++)
      if (array[i] < array[j])
        {
          temp = array[i];
          array[i] = array[j];
          array[j] = temp;
        }
  }

void main(void)
 {
   int values[30], i; 

   for (i = 0; i < 30; i++)
     values[i] = rand() % 100;

   bubble_sort(values, 30);

   for (i = 0; i < 30; i++)
     printf("%d ", values[i]);
 }

