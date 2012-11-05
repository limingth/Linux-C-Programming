#include <stdio.h>

void main(void)
 {
   int row, column;

   float table[3][5] = {{1.0, 2.0, 3.0, 4.0, 5.0},
                        {6.0, 7.0, 8.0, 9.0, 10.0},
                        {11.0, 12.0, 13.0, 14.0, 15.0}};

   for (row = 0; row < 3; row++)
    for (column = 0; column < 5; column++)
     printf("table[%d][%d] = %f\n", row, column, table[row][column]);
 }

