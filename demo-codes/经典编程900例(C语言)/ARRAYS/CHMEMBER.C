#include <stdio.h>

struct Shape {
  int type;
  int color;
  float radius;
  float area;
  float perimeter;
};

void change_structure(struct Shape *shape)
 {
   shape->type = 0;
   shape->color = 1;
   shape->radius = 5.0;
   shape->area = 22.0 / 7.0 * shape->radius * shape->radius; 
   shape->perimeter = 2.0 * 22.0 / 7.0 * shape->radius;
 }

void main(void)
 {
   struct Shape circle;
   
   change_structure(&circle);
   
   printf("circle.type %d\n", circle.type);
   printf("circle.color %d\n", circle.color);
   printf("circle.radius %f circle.area %f circle.perimeter %f\n",
     circle.radius, circle.area, circle.perimeter);
 }

