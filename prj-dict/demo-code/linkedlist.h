/* linkedlist.h */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "word.h"

typedef struct link_node *link;
struct link_node {
	word_t word;
	link next;
};

link make_node(word_t item);
void free_node(link p);
//link search(char * name);
link search(char * key, int * cmp);
void insert(link p);
void delete(link p);
void traverse(void (*visit)(link));
void destroy(void);
void push(link p);
link pop(void);

#endif
