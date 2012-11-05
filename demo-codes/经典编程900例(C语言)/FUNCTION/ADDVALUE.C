#include <stdio.h>
#include <stdarg.h>

int add_values(int value, ...)
 {
    va_list argument_ptr;
    int result = 0;

    if (value != 0)
      {
        result += value;
        va_start(argument_ptr, value);

        while ((value = va_arg(argument_ptr, int)) != 0)
          result += value;

        va_end(argument_ptr);
      }  
    return(result);
 }

void main(void)
 {
   printf("Sum of 3 is %d\n", add_values(3, 0));
   printf("Sum of 3 + 5 is %d\n", add_values(3, 5, 0));
   printf("Sum of 3 + 5 + 8 is %d\n", add_values(3, 5, 8, 0));
   printf("Sum of 3 + 5 + 8 + 9 is %d\n", add_values(3, 5, 8 , 9, 0));
 }
