#ifndef _STACK_H_
#define _STACK_H_

#include <tiny/object.h>
#include <tiny/string.h>
#include <tiny/list.h>

typedef struct _Stack Stack;
struct _Stack
{
	Object parent;

	List* stack;
};

Stack* stack_new();
void stack_destroy(Object* self);

ADT stack_pop(Stack* self);
void stack_push(Stack* self, ADT item);

ADT stack_take(Stack* self);

int stack_get_size(Stack* self);

Bool stack_is_empty(Stack* self);

#endif
