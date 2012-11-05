#include <stdio.h>
#include <stdlib.h>

typedef struct node * link;

struct node 
{
	char item;
	link l;
	link r;
};

link make_node(char c)
{
	link p = (link)malloc(sizeof *p);

	p->item = c;
	p->l = NULL;
	p->r = NULL;

	return p;
}

void free_node(link p)
{
	free(p);
}

void visit(link p)
{
	if (p)
		printf("<%c>\t", p->item);
}

void visit2(link p, int n)
{
	if (p)
		printf("<%c%d>\t", p->item, n);
}

void pre_order(link t)
{
	if (t == NULL)
		return;

	visit(t);
	pre_order(t->l);
	pre_order(t->r);
}

void in_order(link t, int n)
{
	if (t == NULL)
		return;

	in_order(t->l, n+1);
	visit2(t, n);
	in_order(t->r, n+1);
}

void post_order(link t)
{
	if (t == NULL)
		return;

	post_order(t->l);
	post_order(t->r);
	visit(t);
}

int count(link t)
{
	if (!t)
		return 0;

	return 1 + count(t->l) + count(t->r);
}

int depth(link t)
{
	int dl, dr;

	if (!t)
		return 0;

	dl = depth(t->l);
	dr = depth(t->r);

	return 1 + (dl > dr ? dl : dr);
}

void destroy(link t)
{
	if (!t)
		return;

	destroy(t->l);
	t->l = NULL;

	destroy(t->r);
	t->r = NULL;

	free_node(t);
}

link search(link t, char key)
{
	if (!t)
		return NULL;

	if (t->item > key)
		return search(t->l, key);

	if (t->item < key)
		return search(t->r, key);

	return t;
}

link insert(link t, char key)
{
	if (!t)
		return make_node(key);

	if (t->item > key)
		t->l = insert(t->l, key);
	else
		t->r = insert(t->r, key);

	return t;
}

link delete(link t, char key)
{
	link p;

	if (!t)
		return NULL;

	if (t->item > key)
		t->l = delete(t->l, key);

	else if (t->item < key)
		t->r = delete(t->r, key);

	else // ==
	{
		if (t->l == NULL && t->r == NULL)
		{
			free_node(t);
			t = NULL;
		}
		else if (t->l)
			{
				for (p = t->l; p->r; p = p->r)
					;
				t->item = p->item;
				t->l = delete(t->l, t->item);
			}
			else
			{
				for (p = t->r; p->l; p = p->l)
					;
				t->item = p->item;
				t->r = delete(t->r, t->item);
			}
	}

	return t;

}

int main(void)
{
	link tmp = NULL;

	printf("hello, btree!\n");
#if 0
	tmp = make_node('a');
	tmp->r = make_node('b');
	tmp->r->r = make_node('c');
//	tmp->l->l = make_node('a');
//	tmp->l->r = make_node('c');
#else
	tmp = insert(tmp, 'b');
	tmp = insert(tmp, 'a');
	tmp = insert(tmp, 'd');
	tmp = insert(tmp, 'c');
	tmp = insert(tmp, 'e');
	printf("insert ok!\n");
	printf("tmp->item = %c\n", tmp->item);
#endif
	visit(tmp);
	visit(tmp->l);
	visit(tmp->r);
	printf("test oder\n");

	pre_order(tmp);
	printf("pre oder\n");

	post_order(tmp);
	printf("post oder\n");

	in_order(tmp, 1);
	printf("in oder\n");

	printf("count = %d\n", count(tmp));
	printf("depth = %d\n", depth(tmp));
	
//	destroy(tmp);
//	printf("count = %d\n", count(tmp));

	link s = search(tmp, 'd');
	if (s)
	{
		visit(s);
		tmp = delete(tmp, 'd');
		printf("delete node\n");
		in_order(tmp, 1);
		printf("in oder\n");
		printf("count = %d\n", count(tmp));
		printf("depth = %d\n", depth(tmp));

	}
	else
		printf("not found\n");

	return 0;
}
