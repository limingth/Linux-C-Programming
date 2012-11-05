#include <stdio.h>
#include <dos.h>

void main(void)
 {
   if (_8087)
     printf("Math coprocessor found\n");
   else
     printf("No math coprocessor\n");
 }
