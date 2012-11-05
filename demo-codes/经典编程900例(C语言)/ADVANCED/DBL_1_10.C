#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   int i;

   struct ListEntry {
     int number;
     struct ListEntry *next;
     struct ListEntry *previous;
   } start, *node;

   start.next = NULL;  /* Empty list*/

   start.previous = NULL;
   node = &start;      /* Point to the start of the list*/

   for (i = 1; i <= 10; i++)
     {
       node->next = (struct ListEntry *) malloc(sizeof(struct ListEntry));
       node->next->previous = node;
       node = node->next;
       node->number = i;
       node->next = NULL;
     }

    /* Display the list*/

    node = start.next;

    do {
        printf("%d ", node->number);
        node = node->next;
    } while (node->next);  /* Show 10 only one time*/

    do {
        printf("%d ", node->number);
        node = node->previous;
    } while (node->previous);
 }


