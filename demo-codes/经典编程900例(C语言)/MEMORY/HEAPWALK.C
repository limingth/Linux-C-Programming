#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   char *buffer1, *buffer2, *buffer3;

   struct heapinfo node = { NULL, 0, 0};

   buffer1 = malloc(100);
   buffer2 = malloc(200);
   buffer3 = malloc(300);
   free(buffer2);
   
   while (heapwalk(&node) == _HEAPOK)
     printf("Size %u bytes State %s\n", node.size, 
       (node.in_use) ? "In use": "Free");
     
 }
