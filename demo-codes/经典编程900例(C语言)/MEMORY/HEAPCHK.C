#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   char *buffer, *second_buffer;
   int i, state;

   buffer = malloc(100);
   second_buffer = malloc(100);

   state = heapcheck();

   if (state == _HEAPOK)
     printf("Heap is ok\n");
   else if (state == _HEAPCORRUPT)
     printf("Heap is corrupt\n");


   for (i = 0; i <= 100; i++)
     buffer[i] = i;


   state = heapcheck();

   if (state == _HEAPOK)
     printf("Heap is ok\n");
   else if (state == _HEAPCORRUPT)
     printf("Heap is corrupt\n");
 }
