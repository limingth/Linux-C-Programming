#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

btree btree_make_node(char * key)
{
	btree p;

	p = (btree)malloc(sizeof(struct btree_node));
	//p->item = c;
	strcpy(p->wordname, key);
	p->counter = 0;

	p->l = NULL;
	p->r = NULL;

	return p;
}

btree btree_insert(btree p, char * key, word_t * pword)
{
	if (!p)
	{
		btree tmp = btree_make_node(key);
		tmp->counter++;
		tmp->pword = pword;
		return tmp;
	}

	// root is not NULL
	// key belongs to left
	if (strcmp(key, p->wordname) < 0)
		p->l = btree_insert(p->l, key, pword);
	else
		// key belongs to right
		if (strcmp(key, p->wordname) > 0)
			p->r = btree_insert(p->r, key, pword);

	// key is on the tree
	if (strcmp(key, p->wordname) == 0)
		p->counter++;

	return p;
}

void btree_travel(btree p, int layer)
{
	if (!p)
		return;

	btree_travel(p->l, layer+1);
	printf("tree node: <%s> (cnt=%d) layer=%d\n", p->wordname, p->counter, layer);
	btree_travel(p->r, layer+1);
}

btree get_max(btree p)
{
	if (!p)
		return NULL;	

	btree pl = get_max(p->l);
	btree pr = get_max(p->r);

	int lmax = pl? pl->counter : 0;
	int rmax = pr? pr->counter : 0;
	int self = p->counter;

	if (lmax >= self && lmax >= rmax)
		return pl;

	if (rmax >= self && rmax >= lmax)
		return pr;

	return p;
}

int btree_count(btree p)
{
	if (!p)
		return 0;

	return 1 + btree_count(p->l) + btree_count(p->r);
}

int btree_depth(btree p)
{
	if (!p)
		return 0;

	int dl = btree_depth(p->l);
	int dr = btree_depth(p->r);

	int max = dl > dr ? dl : dr;

	return 1 + max;
}

void btree_destroy(btree p)
{
	if (!p)
		return;

	destroy(p->l);
	destroy(p->r);
	free(p);
}

btree btree_search(btree p, char * key, int * cmp)
{
	if (!p)
		return NULL;

	// cmp++
	(*cmp)++;

	//if (p->item == key)
	if (strcmp(p->wordname, key) == 0)
		return p;

	btree tmp = btree_search(p->l, key, cmp);
	if (tmp)
		return tmp;

	tmp = btree_search(p->r, key, cmp);
	if (tmp)
		return tmp;

	return NULL;
}

btree root = NULL;
static FILE * fp;

void btree_save(btree p)
{
	if (!p)
		return;

	btree_save(p->l);
	fprintf(fp, "%s %d\n", p->wordname, p->counter);
	btree_save(p->r);
}


btree btree_savetofile(char * filename)
{
    btree p = root;   

    fp = fopen(filename, "w");

    printf("save btree to file <%s>\n", filename);
    btree_save(root);

    fclose(fp);
}


#if 0
int main(void)
{
	printf("hello, btree! \n");

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

		btree p = search_btree(root, key);
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
#endif
