#include <stdio.h>

int binary_search(int array[], int value, int size)
 {
   int found = 0;
   int high = size, low = 0, mid;

   mid = (high + low) / 2;

   printf("\n\nLooking for %d\n", value);

   while ((! found) && (high >= low))
    {
      printf("Low %d Mid %d High %d\n", low, mid, high);

      if (value == array[mid])
        found = 1;
      else if (value < array[mid])
        high = mid - 1;
      else
        low = mid + 1;

      mid = (high + low) / 2;
   }
  return((found) ? mid: -1);
 }

void main(void)
 {
   int array[100], i;

   for (i = 0; i < 100; i++)
     array[i] = i;

   printf("Result of search %d\n", binary_search(array, 33, 100));
   printf("Result of search %d\n", binary_search(array, 75, 100));
   printf("Result of search %d\n", binary_search(array, 1, 100));
   printf("Result of search %d\n", binary_search(array, 1001, 100));
 }
  


   
