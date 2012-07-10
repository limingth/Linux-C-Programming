#include <stdio.h>
#include <stdlib.h>

typedef struct node * link;

struct node 
{
	char item;
	link next;
};

link make_node(char c)
{
	link p;

	p = (link)malloc(sizeof(struct node));
	p->item = c;
	p->next = NULL;

	return p;
}

void travel(link p)
{
	if (p == NULL)
		return;

	printf("%c \n", p->item);
	travel(p->next);
}

void destory(link p)
{
	link next;

	if (p == NULL)
	{
		printf("destory finished\n");
		return;
	}
	
	next = p->next;
	free(p);

	destory(next);

	return;
}


link head = NULL;

int main(void)
{
	printf("hello, link! \n");

	head = make_node('a');
	head->next = make_node('b');
	head->next->next = make_node('c');

	travel(head);

	destory(head);
	
	return 0;
}
