#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   char *buffer1, *buffer2, *buffer3;
   int i, state;

   buffer1 = malloc(100);
   buffer2 = malloc(200);
   buffer3 = malloc(300);
   free(buffer2);          // Free space in the middle

   state = heapfillfree('A');

   if (state == _HEAPOK)
     printf("Heap is ok\n");
   else if (state == _HEAPCORRUPT)
     printf("Heap is corrupt\n");


   for (i = 0; i <= 150; i++)
     buffer1[i] = i;


   state = heapcheckfree('A');

   if (state == _HEAPOK)
     printf("Heap is ok\n");
   else if (state == _HEAPCORRUPT)
     printf("Heap is corrupt\n");
   else if (state == _BADVALUE)
     printf("Value has been changed in free space\n");
 }
