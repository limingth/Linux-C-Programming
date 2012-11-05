#include <stdio.h>
#include <alloc.h>

void main(void)
 {
   int i;

   struct ListEntry {
     int number;
     struct ListEntry *next;
     struct ListEntry *previous;
   } start, *node, *new;

   start.next = NULL;  /* Empty list*/
   start.previous = NULL;
   node = &start;      /* Point to the start of the list*/

   for (i = 1; i < 10; i += 2)
     {
       node->next = (struct ListEntry *) malloc(sizeof(struct ListEntry));
       node->next->previous = node;
       node = node->next;
       node->number = i;
       node->next = NULL;
     }


   for (i = 2; i <= 10; i += 2)
     {
       int found = 0;

       new = (struct ListEntry *) malloc(sizeof(struct ListEntry));
       new->number = i;
       node = start.next;

       do {
         if (node->number > new->number)
           {
             new->next = node;
             new->previous = node->previous;
             node->previous->next = new;
             node->previous = new;
             found = 1;
           }
         else
           node = node->next;
       } while ((node->next) && (! found));

       if (! found)
        if (node->number > new->number)
          {
             new->next = node;
             new->previous = node->previous;
             node->previous->next = new;
             node->previous = new;
          }
        else
          {
             new->next = NULL;
             new->previous = node;
             node->next = new;
          }
     }

    /* Display the list*/
    node = start.next;
    do {
        printf("%d ", node->number);
        node = node->next;
    } while (node);
 }


