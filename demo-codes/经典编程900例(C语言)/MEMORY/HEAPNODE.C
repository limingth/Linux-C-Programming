#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   char *buffer, *second_buffer;
   int i, state;

   buffer = malloc(100);
   second_buffer = malloc(100);

   state = heapchecknode(buffer);

   if (state == _USEDENTRY)
     printf("buffer is ok\n");
   else
     printf("buffer is not ok\n");

   state = heapchecknode(second_buffer);

   if (state == _USEDENTRY)
     printf("second_buffer is ok\n");
   else
     printf("second_buffer is not ok\n");

   for (i = 0; i <= 100; i++)
     buffer[i] = i;

   state = heapchecknode(buffer);

   if (state == _USEDENTRY)
     printf("buffer is ok\n");
   else
     printf("buffer is not ok\n");

   state = heapchecknode(second_buffer);

   if (state == _USEDENTRY)
     printf("second_buffer is ok\n");
   printf("second_buffer is not ok\n");
 }
