#include <tiny/object.h>

Object* object_new ()
{
	Object* self;

	self = (Object*)mem_new(sizeof(Object));
	object_init_object (OBJECT (self), object_destroy);

	return self;
}

void object_destroy (Object* self)
{
	mem_destroy (self);
}

void object_init_object (Object* self, ObjectDestroy p_destroy)
{
	self->refcount = 1;
	self->destroy = p_destroy;
}

Object* object_addref (Object* self)
{
	if (!self) return NULL;

	self->refcount++;
	return self;
}

void object_unref (Object* self)
{
	if (!self||self->refcount==0) return;

	self->refcount--;
	if (self->refcount <= 0)
	{
		(*self->destroy) (self);
	}
}
