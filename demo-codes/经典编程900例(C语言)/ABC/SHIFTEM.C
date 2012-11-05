#include <stdio.h>

void main(void)
 {
   unsigned u_val = 1;
   signed int value = -1;

   printf("%u (unsigned) shifted left 2 times is %u\n", 
     u_val, u_val << 2);

   printf("%u (unsigned) shifted right 2 times is %u\n", 
     u_val, u_val >> 2);

   u_val = 65535;

   printf("%u (unsigned) shifted left 2 times is %u\n", 
     u_val, u_val << 2);

   printf("%u (unsigned) shifted right 2 times is %u\n", 
     u_val, u_val >> 2);
   
   printf("%d (signed) shifted left 2 times is %d\n", 
     value, value << 2);

   printf("%d (signed) shifted right 2 times is %d\n", 
     value, value >> 2);
 }

