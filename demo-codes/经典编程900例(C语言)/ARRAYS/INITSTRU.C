#include <stdio.h>

void main(void)
 {
   struct Shape {
    int type;
    int color;
    float radius;
    float area;
    float perimeter;
   } circle = {0, 1, 5.0, 78.37, 31.42};
   
   printf("circle.type %d\n", circle.type);
   printf("circle.color %d\n", circle.color);
   printf("circle.radius %f circle.area %f circle.perimeter %f\n",
     circle.radius, circle.area, circle.perimeter);
 }

