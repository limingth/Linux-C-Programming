#include <stdio.h>
#include <stdlib.h>

void shell_sort(int array[], int size)
 {
   int temp, gap, i, exchange_occurred;
          
   gap = size / 2;      
   
   do {
    do {
      exchange_occurred = 0;

      for (i = 0; i < size - gap; i++)
       if (array[i] > array[i + gap])
        {  
          temp = array[i];
          array[i] = array[i + gap];
          array[i + gap] = temp;
          exchange_occurred = 1;
        }
    } while (exchange_occurred);
   } while (gap = gap / 2);
  }

void main(void)
 {
   int values[50], i; 

   for (i = 0; i < 50; i++)
     values[i] = rand() % 100;

   shell_sort(values, 50);

   for (i = 0; i < 50; i++)
     printf("%d ", values[i]);
 }

