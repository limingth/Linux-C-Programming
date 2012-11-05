#include <stdio.h>

void show_string(char *string)
 { 
   while (*string)
     putchar(*string++);
 }

void main(void)
 {
   show_string("Jamsa's 1001 C/C++ Tips");
 }

