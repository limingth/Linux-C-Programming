#include <stdio.h>

void show_2d_array(int array[][10], int rows)
 {
   int i, j;

   for (i = 0; i < rows; i++)
     for (j = 0; j < 10; j++)
       printf("array[%d][%d] = %d\n", i, j, array[i][j]);
 }


void main(void)
 {
   int a[1][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
   int b[2][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                   {11, 12, 13, 14, 15, 16, 17, 18, 19, 20}};
   int c[3][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                   {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
                   {21, 22, 23, 24, 25, 26, 27, 28, 29, 30}};

   show_2d_array(a, 1);
   show_2d_array(b, 2);
   show_2d_array(c, 3);
 }
