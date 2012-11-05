#include <stdio.h>

void main(void)
 {
   int counter = 10;
   int *iptr;          // Declare pointer value

   iptr = &counter;    // Assign the address
   printf("Addres in iptr %x Value at *iptr %d\n", iptr, *iptr); 
   
   *iptr = 25;         // Change the value in memory

   printf("Value of counter %d\n", counter);
 }

