#include <stdio.h>

void show_array(int values[], int number_of_elements)
 {
   int i;

   printf("About to display %d values\n", number_of_elements);
   for (i = 0; i < number_of_elements; i++)
    printf("%d\n", values[i]);
 }

void main(void)
 {
   int scores[5] = {70, 80, 90, 100, 90};
   int count[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   int small[2] = {-33, -44};
                       
   show_array(scores, 5);
   show_array(count, 10);
   show_array(small, 2);
 }

