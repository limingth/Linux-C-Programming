/* linkedlist.c */
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

static link head = NULL;

link make_node(word_t item)
{
	link p = malloc(sizeof *p);
	p->word = item;
	p->next = NULL;
	return p;
}

void free_node(link p)
{
	free(p);
}

link search(char * key, int * counter)
{
	link p;
	int i = 0;

	*counter = 1;
	for (p = head; p; p = p->next, (*counter)++)
	{
		printf("\rcmp %d...", *counter);
		//if (p->item == key)
		if (strcmp(p->word.name, key) == 0)
			return p;
	}
	return NULL;
}

void insert(link p)
{
	p->next = head;
	head = p;
}

void delete(link p)
{
	link pre;
	if (p == head) {
		head = p->next;
		return;
	}
	for (pre = head; pre; pre = pre->next)
		if (pre->next == p) {
			pre->next = p->next;
			return;
		}
}

void traverse(void (*visit)(link))
{
	link p;
	for (p = head; p; p = p->next)
		visit(p);
}

void destroy(void)
{
	link q, p = head;
	head = NULL;
	while (p) {
		q = p;
		p = p->next;
		free_node(q);
	}
}

