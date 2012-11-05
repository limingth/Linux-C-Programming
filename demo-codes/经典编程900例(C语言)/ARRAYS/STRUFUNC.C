#include <stdio.h>

struct Shape {
  int type;
  int color;
  float radius;
  float area;
  float perimeter;
};

void show_structure(struct Shape shape)
 {
   printf("shape.type %d\n", shape.type);
   printf("shape.color %d\n", shape.color);
   printf("shape.radius %f shape.area %f shape.perimeter %f\n",
     shape.radius, shape.area, shape.perimeter);
 }

void main(void)
 {
   struct Shape circle;

   circle.type = 0;
   circle.color = 1;
   circle.radius = 5.0;
   circle.area = 22.0 / 7.0 * circle.radius * circle.radius; 
   circle.perimeter = 2.0 * 22.0 / 7.0 * circle.radius;

   show_structure(circle);
 }

