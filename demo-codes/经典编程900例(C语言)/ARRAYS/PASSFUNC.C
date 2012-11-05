#include <stdio.h>

int get_result(int a, int b, int (*compare)())
 {
   return(compare(a, b));  // Invoke the function passed
 }
 

int max(int a, int b)
 {
   printf("In max\n");
   return((a > b) ? a: b);
 }

int min(int a, int b)
 {
   printf("In min\n");
   return((a < b) ? a: b);
 }

void main(void)
 {
   int result;

   result = get_result(1, 2, &max);
   printf("Max of 1 and 2 is %d\n", result);
   
   result = get_result(1, 2, &min);
   printf("Min of 1 and 2 is %d\n", result);
 }


