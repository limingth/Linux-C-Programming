#include <finc/finctype.h>
#include <finc/finccontext.h>

extern FinCContext* g_finc_context;

FinCType* finc_type_new (FinCTypeType p_type, FinCArrayType p_array_type, unsigned int p_array_size)
{
	FinCType *self;

	self = (FinCType*)mem_new(sizeof(FinCType));
	object_init_object (OBJECT (self), finc_type_destroy);

	self->name = string_new_str("unknown");

	self->type = p_type;
	self->array_type = p_array_type;
	self->array_size = p_array_size;

	return self;
}

FinCType* finc_type_new_copy(FinCType* other)
{
	FinCType* self;

	self = (FinCType*)mem_new(sizeof(FinCType));
	object_init_object ((Object*)self, finc_type_destroy);

	self->name = string_new_str(string_get_str(other->name));
	self->type = other->type;
	self->array_type = other->array_type;
	self->array_size = other->array_size;

	return self;
}

FinCType* finc_type_new_name (unsigned char* p_name, FinCArrayType p_array_type, unsigned int p_array_size)
{
	FinCType* l_type;

	if (strcmp (p_name, "void") == 0)
		return finc_type_new (FinCType_Void, p_array_type, p_array_size);

	if (strcmp (p_name, "char") == 0)
		return finc_type_new (FinCType_Char, p_array_type, p_array_size);

	if (strcmp (p_name, "short") == 0)
		return finc_type_new (FinCType_Short, p_array_type, p_array_size);

	if (strcmp (p_name, "int") == 0)
		return finc_type_new (FinCType_Int, p_array_type, p_array_size);

	#ifdef USING_FLOAT
	if (strcmp (p_name, "float") == 0)
		return finc_type_new (FinCType_Float, p_array_type, p_array_size);
	#endif
	#ifdef USING_DOUBLE
	if (strcmp (p_name, "double") == 0)
		return finc_type_new (FinCType_Double, p_array_type, p_array_size);
	#endif

	if (strcmp (p_name, "bool") == 0)
		return finc_type_new (FinCType_Bool, p_array_type, p_array_size);

	if (strcmp (p_name, "pointer") == 0)
		return finc_type_new (FinCType_Pointer, p_array_type, p_array_size);

	if (strcmp (p_name, "string") == 0)
		return finc_type_new (FinCType_String, p_array_type, p_array_size);

	/*if not base data type, that will be a struct data type*/
	l_type = finc_type_new (FinCType_Struct, p_array_type, p_array_size);
	string_set_str (l_type->name, p_name);

	return l_type;
}

void finc_type_destroy (Object* self)
{
	unref(((FinCType*)self)->name);
	mem_destroy (self);
}

unsigned int finc_type_get_size (FinCType* self)
{
	FinCStruct* l_struct;
	int l_array;
	int l_struct_size;

	if ( self->array_size ) l_array = self->array_size;
	else l_array =1;

	switch ( self->type )
	{
	case FinCType_Char:
		return sizeof(char)*l_array;
	case FinCType_Short:
		return sizeof(short)*l_array;
	case FinCType_Int:
		return sizeof(int)*l_array;
	#ifdef USING_FLOAT
	case FinCType_Float:
		return sizeof(float)*l_array;
	#endif
	#ifdef USING_DOUBLE
	case FinCType_Double:
		return sizeof(double)*l_array;
	#endif
	case FinCType_Bool:
		return sizeof(Bool)*l_array;
	case FinCType_Pointer:
	case FinCType_Func:
		return sizeof(void*)*l_array;
	case FinCType_String:
		return sizeof(unsigned char*)*l_array;
	case FinCType_Struct:
		l_struct = finc_context_get_struct(g_finc_context, self->name);
		if ( !l_struct )
		{
			printf("Error: struct %s not founded.\n", string_get_str (self->name));
			return 0;
		}
		l_struct_size = l_struct->size;
		unref(l_struct);
		return l_struct_size*l_array;
	default:
		return 0;
	}
}
