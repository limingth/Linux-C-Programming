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
	link p = malloc(sizeof(struct node));

	p->item = c;
	p->counter = 0;
	p->l = NULL;
	p->r = NULL;

	return p;
}

void travel(link p)
{
	if (!p)
		return;

	travel(p->l);
	printf("node %c : %d\n", p->item, p->counter);
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

	return 1 + (dl > dr ? dl : dr);
}

link search(link p, char key)
{
	if (!p)
		return NULL;

	if (p->item == key)
		return p;

	link pl = search(p->l, key);
	if (pl)
		return pl;
	
	link pr = search(p->r, key);
	if (pr)
		return pr;

	return NULL;
}

void sum_key(link root, char key)
{
	link node = search(root, key);
	if (node)
	{
		node->counter++;
		//printf("found node %c: %d\n", key, node->counter);
	}
	//else
		//printf("node %c not found! \n", key);
}

link init(char VLR[], char LVR[], int n)
{
	link p;
	int k;

	if (n <= 0)
		return NULL;

	p = make_node(VLR[0]);

	// get k
	for (k = 0; VLR[0] != LVR[k]; k++)
		    ;

	p->l = init(VLR+1, LVR, k);
	p->r = init(VLR+1+k, LVR+k+1, n-k-1);

	return p;
}

int main(void)
{
	link root;

	printf("hello, link & tree \n");
#if 0    
	root = make_node('a');
	root->l = make_node('b');
	root->r = make_node('c');
#endif

#if 0
	root = make_node('a');
	root->l = make_node('b');
	root->r = make_node('c');

	root->l->l = make_node('d');
	root->l->r = make_node('e');

	root->r->l = make_node('f');
	root->r->r = make_node('g');
#endif
	//char VLR[7] = "abdecfg";
	//char LVR[7] = "dbeafcg";	

	char VLR[7] = "dbacfeg";
	char LVR[7] = "abcdefg";	

	root = init(VLR, LVR, 7);

	travel(root);

	int sum = count(root);
	printf("all node is %d\n", sum);

	sum = depth(root);
	printf("nodes depth is %d\n", sum);

	char buf[100] = "abcdsfabdfaaaabbb";
	int i = 0;

	while (buf[i])
	{
		sum_key(root, buf[i]);
		i++;
	}

	printf("input buf is %s\n", buf);
	travel(root);

	return 0;
}
