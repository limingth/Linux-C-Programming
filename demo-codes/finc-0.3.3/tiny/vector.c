#include <tiny/vector.h>
#include <tiny/mem.h>
#include <tiny/object.h>

Vector* vector_new ()
{
	Vector *self;

	self = (Vector*)mem_new(sizeof(Vector));
	object_init_object (OBJECT (self), vector_destroy);

	self->data = NULL;
	self->size = 0;

	return self;
}

void vector_destroy (Object* self)
{
	vector_clear (VECTOR (self));

	mem_destroy (VECTOR (self)->data);
	mem_destroy (self);
}

void vector_clear (Vector* self)
{
	int i;
	for ( i=0; i<vector_get_size(self); i++)
	{
		unref(self->data[i]);
	}
	self->size = 0;
}

Bool vector_is_empty(Vector* self)
{
	return self->size==0? TRUE : FALSE;
}

void vector_resize (Vector* self, int p_newsize)
{
	self->data = mem_resize( self->data, p_newsize * sizeof (Object*));
	self->size = p_newsize;
}

ADT vector_at (Vector* self, int p_index)
{
	if ( (p_index < self->size) && (p_index >=0) ) return addref (Object, self->data[p_index]);
	else return NULL;
}

void vector_set_at (Vector* self, int p_index, ADT p_item)
{
	int old_size, i;

	if ( p_index <0 ) return;
	
	old_size = self->size;
	if ( self->size < p_index+1 ) vector_resize (self, p_index+1);

	for ( i=old_size; i<p_index; i++)
		self->data[i] = NULL;

	self->data[p_index] = addref(Object, p_item);
}

void vector_append (Vector* self, ADT p_item)
{
	self->size++;
	vector_resize (self, self->size);
	self->data[self->size - 1] = addref (Object, p_item);
}

void vector_preppend (Vector* self, ADT p_item)
{
	self->size++;
	vector_resize (self, self->size);
	mem_move ( &(self->data[0]), &(self->data[1]), (self->size-1) * sizeof (Object*) );
	self->data[0] = addref (Object, p_item);
}

void vector_insert (Vector* self, ADT p_item, int p_index)
{
	if ( p_index <=0 )
	{
		vector_preppend(self, p_item);
		return;
	}
	if ( p_index > self->size )
	{
		vector_append(self, p_item);
		return;
	}

	self->size++;
	vector_resize (self, self->size);
	self->data[p_index] = addref(Object, p_item);
}

void vector_remove (Vector* self, int p_index)
{
	if ( p_index <0 || p_index >= self->size ) return;

	self->size--;
	unref (self->data[p_index]);
	mem_copy (&(self->data[p_index + 1]), &(self->data[p_index]), (self->size - p_index) * sizeof (Object*));
}

void vector_foreach(Vector* self, UserFunc user_func, ADT data)
{
	int i;

	if ( self == NULL || user_func == NULL )return;

	for (i = 0; i < self->size; i++)
		(* user_func) (self->data[i], data);
}
