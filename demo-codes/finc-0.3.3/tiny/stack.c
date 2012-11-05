#include <tiny/stack.h>

Stack* stack_new()
{
	Stack* self;

	self = (Stack*) mem_new (sizeof(Stack));
	object_init_object((Object*)self, stack_destroy);

	self->stack = list_new();

	return self;
}

void stack_destroy(Object* self)
{
	unref( ((Stack*)self)->stack );

	mem_destroy(self);
}

ADT stack_pop(Stack* self)
{
	ADT result;

	result = list_last(self->stack);
	list_remove_current(self->stack);

	return result;
}

void stack_push(Stack* self, ADT item)
{
	list_append(self->stack, item);
}


ADT stack_take(Stack* self)
{
	return list_last(self->stack);
}

int stack_get_size(Stack* self)
{
	return list_get_size(self->stack);
}

Bool stack_is_empty(Stack* self)
{
	return list_is_empty(self->stack);
}
