#include <stdio.h>

void main(void)
 {
   int box[3][3];

   float year_sales[52][5];

   char pages[40][60][20];

   printf("Bytes to hold int box[3][3] %d bytes\n", sizeof(box));
   printf("Bytes to hold float year_sales[52][5] %d bytes\n",
     sizeof(year_sales));
   printf("Bytes to hold char pages[40][60][20] %ld bytes\n",
     sizeof(pages));
 }

