#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node * link;

struct node 
{
	char item;
	int counter;
	link l;
	link r;
};


link make_node(char key)
{
	link p;

	p = malloc(sizeof(struct node));

	// init p 
	p->item = key;
	p->counter = 1;
	p->l = NULL;
	p->r = NULL;

	return p;
}

void pre_order(link p)
{
	if (p == NULL)
		return;

	printf("%c(%d) ", p->item, p->counter);
	pre_order(p->l);
	pre_order(p->r);

	return;
}

void in_order(link p, int level, char lr)
{
	if (p == NULL)
		return;

	in_order(p->l, level+1, '<');
	printf("%c%d%c(%d) - ", p->item, level, lr, p->counter);
	in_order(p->r, level+1, '>');

	return;
}

void post_order(link p)
{
	if (p == NULL)
		return;

	post_order(p->l);
	post_order(p->r);
	printf("%c", p->item);

	return;
}

link init(char pre[], char in[], int n)
{
	link t;
	int k;

	if (n == 0)
		return NULL;

	// k is the position of root in in[]
	for (k = 0; pre[0] != in[k]; k++)
		;

	t = make_node(pre[0]);
	t->l = init(pre+1, in, k);
	t->r = init(pre+1+k, in+k+1, n-1-k);

	return t;
}

link search(link p, char key)
{
	if (p == NULL)
		return NULL;

	if (key < p->item)
		return search(p->l, key);
	else if (key > p->item)
		return search(p->r, key);

	// key == p->item
	return p;
}

link insert(link p, char key)
{
	if (p == NULL)
		return make_node(key);

	if (key < p->item)
		p->l = insert(p->l, key);
	else 
	{
		if (key > p->item)
			p->r = insert(p->r, key);
		else //if (key == p->item)
		{
			printf("%c already exists!\n", key);
			p->counter++;
		}
	}

	return p;
}

int main(void)
{
	char pre[] = "4213657";
	char in[] = "1234567";

//	char str[] = "helloworld";
	char str[] = "Don't ask what your country can do for you, but ask what you can do for your country.\n";

	int i = 0;

	int state = 0;	// init state
	int input = 0;	// 0: space		1: alpha

	link root = NULL;

	printf("hello, btree!\n");
	printf("%s", str);

#if 0
	root = make_node('a');
	root->l = make_node('b');
	root->r = make_node('c');
#endif

#if 0
	root = make_node('4');
	root->l = make_node('2');
	root->r = make_node('6');

	root->l->l = make_node('1');
	root->l->r = make_node('3');
	root->r->l = make_node('5');
	root->r->r = make_node('7');
#endif

	//root = init(pre, in, 7);

	while (1)
	{
		char c;

		c = getchar();
		if (c == EOF)
			break;

		printf("insert %c \n", c);
		root = insert(root, c);
	}

#if 0
	for (i = 0; i < strlen(str); i++)
	{
		printf("insert %c \n", str[i]);
		root = insert(root, str[i]);
	}
#endif

	//pre_order(root);
	//printf("\npre travel finished\n");

	in_order(root, 0, '^');
	printf("\nin travel finished\n");

	//post_order(root);
	//printf("\npost travel finished\n");

	return 0;
}
