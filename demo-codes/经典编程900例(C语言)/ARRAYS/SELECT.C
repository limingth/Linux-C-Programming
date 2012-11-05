#include <stdio.h>
#include <stdlib.h>

void selection_sort(int array[], int size)
 {
   int temp, current, j;

   for (current = 0; current < size; current++) 
    for (j = current + 1; j < size; j++)
      if (array[current] > array[j])
        {
          temp = array[current];
          array[current] = array[j];
          array[j] = temp;
        }
  }

void main(void)
 {
   int values[30], i; 

   for (i = 0; i < 30; i++)
     values[i] = rand() % 100;

   selection_sort(values, 30);

   for (i = 0; i < 30; i++)
     printf("%d ", values[i]);
 }

