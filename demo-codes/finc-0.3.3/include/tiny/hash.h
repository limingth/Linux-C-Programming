#ifndef _HASH_H_
#define _HASH_H_

#include <tiny/global.h>

typedef unsigned int (*HashFunc) (void* key);

typedef struct _HashTable  HashTable;

/* 
 *Hash tables
 */
HashTable* hash_table_new (HashFunc hash_func, EqualFunc key_equal_func);

void hash_table_destroy (Object* hash_table);

void* hash_table_find (HashTable* hash_table, void* key);

void hash_table_insert (HashTable* hash_table, void* key, void* value);

Bool hash_table_remove (HashTable* hash_table, void* key);

void hash_table_foreach(HashTable* hash_table, UserFunc user_func, void* data);

unsigned int hash_table_get_size (HashTable* hash_table);

/* Hash Functions
 */
unsigned int direct_hash (void* v);

#endif
