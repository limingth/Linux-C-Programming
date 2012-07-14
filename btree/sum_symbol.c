#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node * link;

struct node 
{
	char item[32];
	int counter;
	link l;
	link r;
};


link make_node(char * key)
{
	link p;

	p = malloc(sizeof(struct node));

	// init p 
	strcpy(p->item, key);
	p->counter = 1;
	p->l = NULL;
	p->r = NULL;

	return p;
}

void in_order(link p, int level, char lr)
{
	if (p == NULL)
		return;

	in_order(p->l, level+1, '<');
	printf("%s%d%c(%d) - ", p->item, level, lr, p->counter);
	in_order(p->r, level+1, '>');

	return;
}

link search(link p, char * key)
{
	if (p == NULL)
		return NULL;

	if (strcmp(key, p->item) < 0)
		return search(p->l, key);
	else if (strcmp(key, p->item) > 0)
		return search(p->r, key);

	// key == p->item
	return p;
}

link insert(link p, char * key)
{
	if (p == NULL)
		return make_node(key);

	if (strcmp(key, p->item) < 0)
		p->l = insert(p->l, key);
	else 
	{
		if (strcmp(key, p->item) > 0)
			p->r = insert(p->r, key);
		else //if (key == p->item)
		{
			printf("node <%s> already exists!\n", key);
			p->counter++;
		}
	}

	return p;
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

link delete(link t, char * key)
{
	if (!t)
		return NULL;

	if (strcmp(key, t->item) < 0)
		t->l = delete(t->l, key);
	else
	if (strcmp(key, t->item) > 0)
		t->r = delete(t->r, key);
	else // do delete t!
	{
		if (t->l == NULL && t->r == NULL)
		{
			free(t);
			t = NULL;
			// return NULL;
		}
		else
		{
			if (t->l) // left is not NULL
			{
				link p;
				for (p = t->l; p->r; p = p->r)
					;
				//t->item = p->item;
				strcpy(t->item, p->item);
				t->counter = p->counter;
				t->l = delete(t->l, p->item);
			}
			else
			{ // left is NULL
				link p;
				for (p = t->r; p->l; p = p->r)
					;
				//t->item = p->item;
				strcpy(t->item, p->item);
				t->counter = p->counter;
				t->r = delete(t->r, p->item);
			}
		}
	}
	return t;
}

int get_input_type(char c)
{
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		return 1;

	if (c == '.' || c == '\\')
		return 1;

	if (c >= '0' && c <= '9')
		return 2;

	return 0;
}

/*
 		state machine design

	input:	0(' ')		1('a')		2('9')
---------------------------------------------
state:
0: " "		0			1			2
1: "a"		0			1			1
2: "9"		0			3			2
3: "9a"		0			3			3
*/

int main(void)
{
	char pre[] = "4213657";
	char in[] = "1234567";

	int i = 0;

	int state = 0;	// init state
	int input = 0;	// 0: space		1: alpha	2: digit

	link root = NULL;

	printf("hello, btree!\n");

	while (1)
	{
		char c;
		char wordbuf[32];

		c = getchar();
		if (c == EOF)
			break;

		input = get_input_type(c);
		//printf("state = %d ", state);

		switch (state)
		{	
		case 0:		//" "
			switch (input)
			{
			case 0:
				break;

			case 1:
			case 2:
				//state = 1;
				state = input;
				//printf("word begin with <%c>\n", c);
				i = 0;
				wordbuf[i++] = c;
				break;

			default:
				break;
			}
			break;

		case 1:		// "a"
			switch (input)
			{
			case 0:
				wordbuf[i] = '\0';
				printf("word found! value = <%s>\n", wordbuf);

				// insert to btree
				printf("insert %s(%d)\n", wordbuf, input);
				root = insert(root, wordbuf);

				state = 0;
				break;

			case 1:
			case 2:
				wordbuf[i++] = c;
				break;

			default:
				break;
			}
			break;

		case 2:		// "9"
			switch (input)
			{
			case 0:
				wordbuf[i] = '\0';
				printf("number found! value = <%s>\n", wordbuf);
				state = 0;
				break;

			case 1:
				wordbuf[i++] = c;
				state = 3;
				break;

			case 2:
				wordbuf[i++] = c;
				state = 2;
				break;

			default:
				break;
			}
			break;

		case 3:		// "9a"
			switch (input)
			{
			case 0:
				wordbuf[i] = '\0';
				printf("Error word found! value = <%s>\n", wordbuf);
				state = 0;
				break;

			case 1:
			case 2:
				wordbuf[i++] = c;
				state = 3;
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	in_order(root, 0, '^');
	printf("\nin travel finished\n");

	link p;
	p = get_max(root);
	printf("-> max node is <%s>(%d)\n", p->item, p->counter);

	delete(root, p);

	in_order(root, 0, '^');
	printf("\nin travel finished\n");

	p = get_max(root);
	printf("-> max node is <%s>(%d)\n", p->item, p->counter);

	return 0;
}
