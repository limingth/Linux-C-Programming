#include <stdio.h>
#include <stdlib.h>

#include <tiny/hash.h>

#define HASH_TABLE_MIN_SIZE 11
#define HASH_TABLE_MAX_SIZE 13845163

typedef struct _HashNode HashNode;
struct _HashNode
{
	void* key;
	void* value;
	HashNode *next;
};

struct _HashTable
{
	Object parent;

	int size;
	int nnodes;
	HashNode **nodes;
	HashFunc hash_func;
	EqualFunc key_equal_func;
};

static const unsigned int primes[] =
    {
        11,
        19,
        37,
        73,
        109,
        163,
        251,
        367,
        557,
        823,
        1237,
        1861,
        2777,
        4177,
        6247,
        9371,
        14057,
        21089,
        31627,
        47431,
        71143,
        106721,
        160073,
        240101,
        360163,
        540217,
        810343,
        1215497,
        1823231,
        2734867,
        4102283,
        6153409,
        9230113,
        13845163,
    };

static const unsigned int nprimes = sizeof (primes) / sizeof (primes[0]);

static void hash_table_resize (HashTable *hash_table);
static HashNode** hash_table_find_node (HashTable *hash_table, void* key);
static HashNode* hash_node_new (void* key, void* value);
static void hash_node_destroy (HashNode *hash_node);
static void hash_nodes_destroy (HashNode *hash_node);
static unsigned int primes_closest (unsigned int num);
static void hash_table_needresize(HashTable *hash_table);

HashTable* hash_table_new (HashFunc hash_func, EqualFunc key_equal_func)
{
	HashTable *hash_table;

	hash_table = mem_new ( sizeof(HashTable) );
	object_init_object (OBJECT (hash_table), hash_table_destroy);

	hash_table->size               = HASH_TABLE_MIN_SIZE;
	hash_table->nnodes             = 0;
	hash_table->hash_func          = hash_func ? hash_func : direct_hash;
	hash_table->key_equal_func     = key_equal_func;
	hash_table->nodes              = mem_new ( sizeof(HashNode*) * hash_table->size);

	mem_set(hash_table->nodes, 0, sizeof(HashNode*) * hash_table->size);

	return hash_table;
}

void hash_table_destroy (Object *hash_table)
{
	unsigned int i;
	HashTable* real_table = (HashTable*)hash_table;

	if ( real_table == NULL )return;

	for (i = 0; i < real_table->size; i++)
		hash_nodes_destroy (real_table->nodes[i]);

	mem_destroy (real_table->nodes);
	mem_destroy (real_table);
}

static HashNode** hash_table_find_node (HashTable *hash_table, void* key)
{
	HashNode **node;

	node = &hash_table->nodes [(* hash_table->hash_func) (key) % hash_table->size];

	if (hash_table->key_equal_func)
		while (*node && !(*hash_table->key_equal_func) ((*node)->key, key))
			node = &(*node)->next;
	else
		while (*node && (*node)->key != key)
			node = &(*node)->next;

	return node;
}

ADT hash_table_find (HashTable* hash_table, ADT key)
{
	HashNode *node;
	if ( hash_table == NULL || key == NULL) return NULL;

	node = *hash_table_find_node (hash_table, key);

	if ( node ) return addref(ADT, node->value);
	else return NULL;
}

void hash_table_insert (HashTable *hash_table, ADT key, ADT value)
{
	HashNode **node;

	if ( hash_table == NULL )return;

	node = hash_table_find_node (hash_table, key);

	if (*node)
	{
		unref((*node)->value);
		(*node)->value = addref(void*, value);
	}
	else
	{
		*node = hash_node_new (key, value);
		hash_table->nnodes++;
		hash_table_needresize (hash_table);
	}
}

Bool hash_table_remove (HashTable *hash_table, ADT  key)
{
	HashNode **node, *dest;

	if ( hash_table ==NULL ) return FALSE;

	node = hash_table_find_node (hash_table, key);
	if (*node)
	{
		dest = *node;
		(*node) = dest->next;
		hash_node_destroy (dest);
		hash_table->nnodes--;

		hash_table_needresize (hash_table);

		return TRUE;
	}

	return FALSE;
}

void hash_table_foreach(HashTable *hash_table, UserFunc user_func, ADT data)
{
	HashNode *node;
	int i;

	if ( hash_table == NULL || user_func == NULL )return;

	for (i = 0; i < hash_table->size; i++)
		for (node = hash_table->nodes[i]; node; node = node->next)
			(* user_func) (node->value, data);
}

unsigned int hash_table_get_size (HashTable *hash_table)
{
	if ( hash_table ==NULL ) return 0;

	return hash_table->nnodes;
}

static void hash_table_needresize(HashTable *hash_table)
{
	if ((hash_table->size >= 3*hash_table->nnodes && hash_table->size > HASH_TABLE_MIN_SIZE) ||
	        (3 * hash_table->size <= hash_table->nnodes && hash_table->size < HASH_TABLE_MAX_SIZE))
		hash_table_resize (hash_table);
}

static void hash_table_resize (HashTable *hash_table)
{
	HashNode **new_nodes;
	HashNode *node;
	HashNode *next;
	unsigned int hash_val;
	int new_size;
	int i;

	i = primes_closest(hash_table->nnodes);
	new_size = i > HASH_TABLE_MAX_SIZE ? HASH_TABLE_MAX_SIZE : i < HASH_TABLE_MIN_SIZE ? HASH_TABLE_MIN_SIZE : i ;

	new_nodes = mem_new ( sizeof(HashNode*) * new_size);
	mem_set(new_nodes, 0, sizeof(HashNode*) * new_size);

	for (i = 0; i < hash_table->size; i++)
		for (node = hash_table->nodes[i]; node; node = next)
		{
			next = node->next;

			hash_val = (* hash_table->hash_func) (node->key) % new_size;

			node->next = new_nodes[hash_val];
			new_nodes[hash_val] = node;
		}

	mem_destroy (hash_table->nodes);
	hash_table->nodes = new_nodes;
	hash_table->size = new_size;
}

static HashNode* hash_node_new (ADT key, ADT value)
{
	HashNode *hash_node;

	hash_node = mem_new ( sizeof(HashNode) );

	hash_node->key = addref(ADT, key);
	hash_node->value = addref(ADT, value);;

	hash_node->next = NULL;

	return hash_node;
}

static void hash_node_destroy (HashNode *hash_node)
{
	unref(hash_node->key);
	hash_node->key = NULL;

	unref(hash_node->value);
	hash_node->value = NULL;

	mem_destroy(hash_node);
}

static void hash_nodes_destroy (HashNode *hash_node)
{
	if (hash_node)
	{
		HashNode *node = hash_node;
		HashNode *temp;

		while (node->next)
		{
			unref(node->key);
			node->key = NULL;

			unref(node->value);
			node->value = NULL;

			temp = node;
			node = node->next;
			mem_destroy(temp);
		}

		unref(node->key);
		node->key = NULL;

		unref(node->value);
		node->value = NULL;
		mem_destroy(node);
	}
}

static unsigned int primes_closest (unsigned int num)
{
	int i;

	for (i = 0; i < nprimes; i++)
		if (primes[i] > num)
			return primes[i];

	return primes[nprimes - 1];
}

unsigned int direct_hash (ADT v)
{
	return (unsigned int)v;
}
