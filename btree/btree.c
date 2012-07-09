#include <stdio.h>
#include <stdlib.h>

typedef struct node * link;

struct node 
{
	char item;
	int counter;
	link l;
	link r;
};

link make_node(char c)
{
	link p;

	p = (link)malloc(sizeof(struct node));
	p->item = c;
	p->counter = 0;

	p->l = NULL;
	p->r = NULL;

	return p;
}

void travel(link p)
{
	if (p == NULL)
		return;

	printf("%c: counter = %d\n", p->item, p->counter);
	travel(p->l);
	travel(p->r);
}

int count(link p)
{
	if (!p)
		return 0;

	return 1 + count(p->l) + count(p->r);
}

int depth(link p)
{
	if (!p)
		return 0;

	int dl = depth(p->l);
	int dr = depth(p->r);

	int max = dl > dr ? dl : dr;

	return 1 + max;
}

void destroy(link p)
{
	if (!p)
		return;

	destroy(p->l);
	destroy(p->r);
	free(p);
}

link search_btree(link p, char key)
{
	if (!p)
		return NULL;

	if (p->item == key)
		return p;

	link tmp = search_btree(p->l, key);
	if (tmp)
		return tmp;

	tmp = search_btree(p->r, key);
	if (tmp)
		return tmp;

	return NULL;
}

link root = NULL;

int main(void)
{
	printf("hello, link! \n");

	root = make_node('4');
	root->l = make_node('2');
	root->r = make_node('5');

	root->l->l = make_node('1');
	root->l->r = make_node('3');
	root->r->r = make_node('6');
	root->r->l = make_node('7');

	travel(root);

	printf("count root = %d\n", count(root));
	printf("depth root = %d\n", depth(root));

	char str[] = "1231215";
	int i = 0;

	while (str[i])
	{
		char key = str[i];

		link p = search_btree(root, key);
		if (p)	// p: not NULL, then key is on the tree
		{
			p->counter++;
			printf("found key: %c (%d)\n", key, p->counter);
		}
		else
			printf("not found key: %c \n", key);

		i++;
	}

	travel(root);

	destroy(root);
	printf("destroy root ok!\n");

	return 0;
}
