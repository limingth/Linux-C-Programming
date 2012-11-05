#include <finc/fincvar.h>

FinCVar* finc_var_new (String* p_name, FinCData* p_data)
{
	FinCVar *self;

	self = (FinCVar*)mem_new(sizeof(FinCVar));
	object_init_object (OBJECT (self), finc_var_destroy);

	self->name = addref (String, p_name);
	self->data = addref (FinCData, p_data);

	return self;
}

FinCVar* finc_var_new_copy (String* p_name, FinCData* p_data)
{
	FinCVar *self;

	self = (FinCVar*)mem_new(sizeof(FinCVar));
	object_init_object (OBJECT (self), finc_var_destroy);

	self->name = addref (String, p_name);
	self->data = finc_data_new_copy(p_data);

	return self;
}

void finc_var_destroy (Object* self)
{
	unref ( ((FinCVar*)self)->name );
	unref ( ((FinCVar*)self)->data );

	mem_destroy (self);
}
