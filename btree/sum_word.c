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

int get_input_type(char c)
{
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		return 1;

	if (c >= '0' && c <= '9')
		return 2;

	return 0;
}

int main(void)
{
	char pre[] = "4213657";
	char in[] = "1234567";

//	char str[] = "helloworld";
	char str[] = "Don't ask what your country can do for you, but ask what you can do for your country.\n";

	int i = 0;
	int pos = 0;

	int state = 0;	// init state
	int input = 0;	// 0: space		1: alpha

	link root = NULL;

	printf("hello, btree!\n");
	printf("%s", str);

	while (1)
	{
		char c;
		char wordbuf[32];

		c = str[pos++];
		if (c == '\0')
			break;

		input = get_input_type(c);
		//printf("state = %d ", state);
		
#if 1
		if (state == 0 && input == 1)
		{
			state = 1;
			//printf("word begin with <%c>\n", c);
			i = 0;
			wordbuf[i++] = c;
		} else if (state == 1 && input == 0)
		{
			wordbuf[i] = '\0';
			printf("word end value = <%s>\n", wordbuf);

			printf("insert %s(%d)\n", wordbuf, input);
			root = insert(root, wordbuf);
			state = 0;
		} else if (state == 1 && input == 1)
			wordbuf[i++] = c;
#endif

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
