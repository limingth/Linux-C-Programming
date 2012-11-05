#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   int i;

   struct ListEntry {
     int number;
     struct ListEntry *next;
   } start, *node, *previous;

   start.next = NULL;  // Empty list
   node = &start;      // Point to the start of the list

   for (i = 1; i <= 10; i++)
     {
       node->next = (struct ListEntry *) malloc(sizeof(struct ListEntry));
       node = node->next;
       node->number = i;
       node->next = NULL;
     }

    // Remove the number 5
    node = start.next;
    previous = &start;

    while (node)
      if (node->number == 5)
        {
          previous->next = node->next;
          free(node);
          break;       // End the loop
        }
      else
        {
          node = node->next;
          previous = previous->next;
        }


    // Display the list
    node = start.next;
    while (node)
      {
        printf("%d ", node->number);
        node = node->next;
      }
 }


