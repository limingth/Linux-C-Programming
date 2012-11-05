#ifndef _FINC_STRUCT_H_
#define _FINC_STRUCT_H_

#include <tiny/global.h>
#include <tiny/hash.h>
#include <tiny/string.h>
#include <tiny/vector.h>

#include <finc/fincconfig.h>
#include <finc/fincfield.h>

#define FinC_STRUCT(obj) ((FinCStruct*) obj)

typedef struct _FinCStruct FinCStruct;
struct _FinCStruct
{
	Object parent;
	String* name;

	HashTable* hash_field;

	int size;
	int next_index;
};

FinCStruct* finc_struct_new(String* p_name);
void finc_struct_destroy(Object* self);

Vector* finc_struct_init_data(FinCStruct* self, ADT p_raw);

void finc_struct_add_field (FinCStruct* self, FinCField* p_field);
#define finc_struct_get_field( struct_t , name) \
        (struct_t)? (FinCField*)hash_table_find((struct_t)->hash_field, (ADT)(name)) : NULL

/*
get the field offset in data block.
*/
int finc_struct_get_field_offset (FinCStruct* self, String* p_name);
int finc_struct_get_field_index (FinCStruct* self, String* p_name);

#define finc_struct_get_size(struct_t)	(struct_t)? (struct_t)->size : NULL

#endif
