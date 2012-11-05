#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(char *array[], int size)
 {
   char *temp; 
   int i, j;

   for (i = 0; i < size; i++) 
    for (j = 0; j < size; j++)
      if (strcmp(array[i], array[j]) < 0)
        {
          temp = array[i];
          array[i] = array[j];
          array[j] = temp;
        }
  }

void main(void)
 {
   char *values[] = {"AAA", "CCC", "BBB", "EEE", "DDD"};
   int i;

   bubble_sort(values, 5);

   for (i = 0; i < 5; i++)
     printf("%s ", values[i]);
 }

