#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   int i, found;

   struct ListEntry {
     int number;
     struct ListEntry *next;
     struct ListEntry *previous;
   } start, *node;

   start.next = NULL;  // Empty list
   start.previous = NULL;
   node = &start;      // Point to the start of the list

   for (i = 1; i <= 10; i++)
     {
       node->next = (struct ListEntry *) malloc(sizeof(struct ListEntry));
       node->next->previous = node;
       node = node->next;
       node->number = i;
       node->next = NULL;
     }

    // Remove the entry
    node = start.next;
    found = 0;
    do {
        if (node->number == 7)
          {
            found = 1;
            node->previous->next = node->next;
            node->next->previous = node->previous;
            free(node);
          }
        else
          node = node->next;
    } while ((node) && (! found));  // Show 10 only one time   

    node = start.next;
    do {
        printf("%d ", node->number);
        node = node->next;
    } while (node);
 }


