#include <stdio.h>

void main(void)
 {
   int employee_number = 12345;
   char region[] = "SEA";
   char filename[64];

   sprintf(filename, "%s%d", region, employee_number);

   printf("Employee filename: %s\n", filename);
 }
