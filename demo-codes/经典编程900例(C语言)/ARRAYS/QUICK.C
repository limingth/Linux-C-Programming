#include <stdio.h>
#include <stdlib.h>

void quick_sort(int array[], int first, int last)
 {
   int temp, low, high, list_separator;    
   
   low = first;
   high = last;
   list_separator = array[(first + last) / 2];

   do {
     while (array[low] < list_separator)
       low++;

     while (array[high] > list_separator)
       high--;
   
     if (low <= high)
      {  
        temp = array[low];
        array[low++] = array[high];
        array[high--] = temp;
      }
   } while (low <= high);

  if (first < high)
    quick_sort(array, first, high);
  if (low < last)
    quick_sort(array, low, last);
 }

void main(void)
 {
   int values[100], i; 

   for (i = 0; i < 100; i++)
     values[i] = rand() % 100;

   quick_sort(values, 0, 99);

   for (i = 0; i < 100; i++)
     printf("%d ", values[i]);
 }

