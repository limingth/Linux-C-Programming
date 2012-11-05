#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <tiny/global.h>

#define OBJECT(obj) ((Object*) obj)

typedef struct _Object Object;
typedef void (*ObjectDestroy) (Object* self);
struct _Object
{
	int refcount;

	ObjectDestroy destroy;
};

Object* object_new ();

void object_destroy (Object* self);

void object_init_object (Object* self, ObjectDestroy p_destroy);

Object* object_addref (Object* self);

void object_unref (Object* self);

#endif
