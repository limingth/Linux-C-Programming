#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <tiny/global.h>

#define VECTOR(obj) ((Vector*) obj)

typedef struct _Vector Vector;
struct _Vector
{
	Object parent;

	Object** data;
	unsigned int size;
};

Vector* vector_new ();

void vector_destroy (Object* self);

void vector_clear (Vector* self);

Bool vector_is_empty(Vector* self);

#define vector_get_size(self)	(self)->size

void vector_resize (Vector* self, int p_newsize);

ADT vector_at (Vector* self, int p_index);

void vector_set_at (Vector* self, int p_index, ADT p_item);

void vector_append (Vector* self, ADT p_item);

void vector_preppend (Vector* self, ADT p_item);

void vector_insert (Vector* self, ADT p_item, int p_index);

void vector_remove (Vector* self, int p_index);

void vector_foreach(Vector* self, UserFunc user_func, ADT data);

#endif
