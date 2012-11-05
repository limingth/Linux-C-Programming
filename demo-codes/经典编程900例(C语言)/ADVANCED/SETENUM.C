#include <stdio.h>

void main(void)
 {
   enum weekdays { Monday = 10, Tuesday = 20, 
                   Wednesday = 30, Thursday = 40,
                   Friday = 50 };

 
   printf("%d %d %d %d %d\n", Monday, Tuesday, Wednesday,
     Thursday, Friday);
 }

