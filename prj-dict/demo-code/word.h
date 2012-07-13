// one word 
struct word
{
	char name[32];
	char meaning[256];
};

typedef struct word word_t;

#if 0
// link list
struct list_node
{
	word_t word;
	struct list_node * next;
}

// binary tree 
struct tree_node
{
	//word_t * p;
	char wordname[32];
	int counter;
	struct tree_node * l, r;
}

// btree to file btree.txt
---------------------
akaedu 32
book 15
abb 1
---------------------
#endif
