#include <stdio.h>

void main ()
 {
   int value = 255;

   printf("The decimal value %d in octal is %#o\n",
        value, value);

   printf("The decimal value %d in hexadecimal is %#x\n", 
        value, value);

   printf("The decimal value %d in hexadecimal is %#X\n", 
        value, value);
 }

