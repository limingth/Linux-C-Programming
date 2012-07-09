#include <stdio.h>
#include <stdlib.h>

typedef struct node * link;
struct node {
	char item;
	int counter;

	link l, r;
};

link make_node(char key)
{
	link p = (link)malloc(sizeof(struct node));

	p->item = key;
	p->counter = 0;

	p->l = p->r = NULL;
	
	return p;
}

link search(link p, char key)
{
	if (!p)
		return NULL;
	
	if (key < p->item)
		return search(p->l, key);

	if (key > p->item)
		return search(p->r, key);

	// key == p->item
	return p;
}

link insert(link p, char key)
{
	if (!p)
	{
		link tmp = make_node(key);
		tmp->counter++;
		return tmp;
	}

	// root is not NULL
	// key belongs to left
	if (key < p->item)
		p->l = insert(p->l, key);
	else
		// key belongs to right
		if (key > p->item)
			p->r = insert(p->r, key);

	// key is on the tree
	if (key == p->item)
		p->counter++;

	return p;
}

void travel(link p, int layer)
{
	if (!p)
		return;

	travel(p->l, layer+1);
	printf("node: %c (c=%d) l=%d\n", p->item, p->counter, layer);
	travel(p->r, layer+1);

	return;
}

link get_max(link p)
{
	if (!p)
		return NULL;

	link pl = get_max(p->l);		
	link pr = get_max(p->r);		

	int lmax = pl? pl->counter : 0;
	int rmax = pr? pr->counter : 0;
	int self = p->counter;

	if (lmax >= self && lmax >= rmax)
		return pl;
	
	if (rmax >= self && rmax >= lmax)
		return pr;

	return p;
}

link gmax = NULL;

link get_max2(link p)
{
	if (!p)
		return NULL;

	if (!gmax)
		gmax = p;

	if (p->counter > gmax->counter)
		gmax = p;

	get_max2(p->l);
	get_max2(p->r);

	return gmax;
}

link delete(link t, char key)
{
	if (!t)
		return NULL;

	if (key < t->item)
		t->l = delete(t->l, key);
	else
		if (key > t->item)
			t->r = delete(t->r, key);
		else	// do delete t!
		{
			if (t->l == NULL && t->r == NULL)
			{
				free(t);
				t = NULL;
				// return NULL;
			}
			else
			{
				if (t->l)	// left is not NULL
				{
					link p;
					for (p = t->l; p->r; p = p->r)
						;
					t->item = p->item;
					t->counter = p->counter;
					t->l = delete(t->l, p->item);
				}
				else
				{	// left is NULL
					link p;
					for (p = t->r; p->l; p = p->r)
						;
					t->item = p->item;
					t->counter = p->counter;
					t->r = delete(t->r, p->item);
				}
			}
		}
	return t;
}

int main(void)
{	
//	char buf[] = "hello,world";
	char buf[] = "hello, akaedu aaa kkk uu";
	char c;
	int i = 0;
	link root = NULL; 

	printf("hello, sumary alpha\n");

	printf("buf = %s\n", buf);

	while ((c = buf[i]) != '\0')
	{
		printf("%c\n", c);

	//	link tmp = make_node(c);
		if (isalpha(c))
			root = insert(root, c);

		i++;
	}

	travel(root, 0);
#if 0
	char key;

	printf("please input a node name: ");
	scanf("%c", &key);

	link p = search(root, key);
	if (p)
		printf("find node: %c c=%d \n", p->item, p->counter);
	else
		printf("not find node: %c!\n", key);
#endif

	// get max counter node
	link max;

	max = get_max(root);
	printf("max node %c: c=%d \n", max->item, max->counter);
	
	//max = get_max2(root);
	//printf("max node %c: c=%d \n", max->item, max->counter);

	while ((max = get_max(root)) != NULL)
	{
		printf("now max node %c: c=%d \n", max->item, max->counter);
		root = delete(root, max->item);
	//	max->counter = 0;
	}

	return 0;
}
