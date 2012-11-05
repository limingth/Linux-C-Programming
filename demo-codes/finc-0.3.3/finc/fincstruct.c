#include <finc/fincstruct.h>
#include <finc/fincdata.h>

static void private_finc_struct_init_data(ADT value, ADT data);

FinCStruct* finc_struct_new(String* p_name)
{
    FinCStruct *self;

    self = (FinCStruct*)mem_new (sizeof(FinCStruct));
    object_init_object (OBJECT (self), finc_struct_destroy);

    self->name = addref (String, p_name);
    self->hash_field = hash_table_new (string_hash, string_equal);

	self->size = 0;
	self->next_index = 0;

    return self;
}

void finc_struct_destroy(Object* self)
{
    unref(((FinCStruct*)self)->name);
    unref(((FinCStruct*)self)->hash_field);

    mem_destroy (self);
}

ADT private_data_p=NULL;

Vector* finc_struct_init_data(FinCStruct* self, ADT p_raw)
{
    Vector* l_vector;
	ADT old_data;

	old_data = private_data_p;
    private_data_p = p_raw;
    l_vector = vector_new();
    hash_table_foreach(self->hash_field, private_finc_struct_init_data, l_vector);
    private_data_p = old_data;

    return l_vector;
}

void private_finc_struct_init_data(ADT value, ADT data)
{
    FinCField* l_field;
    Vector* l_vector;
    FinCData* l_data;

    l_field  = (FinCField*)value;
    l_vector = (Vector*)data;

    l_data = finc_data_new( l_field->type, (char*)private_data_p + l_field->offset);
    vector_set_at(l_vector, l_field->index, (ADT)l_data);
    unref(l_data);
}

void finc_struct_add_field (FinCStruct* self, FinCField* p_field)
{
    finc_field_set_offset(p_field, self->size);
    finc_field_set_index(p_field, self->next_index++);

    self->size += finc_type_get_size(p_field->type);
    hash_table_insert(self->hash_field, (ADT)p_field->name, OBJECT(p_field));
}

int finc_struct_get_field_offset (FinCStruct* self, String* p_name)
{
	FinCField* l_field;
	int l_offset;

	l_field = finc_struct_get_field (self, p_name);

	l_offset = finc_field_get_offset(l_field);
	unref(l_field);

	return l_offset;
}

int finc_struct_get_field_index (FinCStruct* self, String* p_name)
{
	FinCField* l_field;
	int l_index;

	l_field = finc_struct_get_field (self, p_name);

	l_index = finc_field_get_index(l_field);
	unref(l_field);

	return l_index;
}
