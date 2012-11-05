#include <stdio.h>

void show_array(int values[], int number_of_elements)
 {
   int i;

   for (i = 0; i < number_of_elements; i++)
    printf("%d\n", values[i]);
 }

void main(void)
 {
   int scores[5] = {70, 80, 90, 100, 90};

   show_array(scores, 5);
 }

