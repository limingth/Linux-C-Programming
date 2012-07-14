
#include "word.h"

typedef struct btree_node * btree;

struct btree_node 
{
	char wordname[32];
	int counter;
	word_t * pword;
	btree l;
	btree r;
};

btree btree_make_node(char * key);

btree btree_search(btree p, char * key, int * cmp);

//btree btree_insert(btree p, char * key);
btree btree_insert(btree p, char * key, word_t * pword);
