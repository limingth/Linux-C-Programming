#include <finc/fincdata.h>
#include <finc/fincfield.h>
#include <finc/fincstruct.h>
#include <finc/finccontext.h>
#include <finc/finclib.h>

FinCData* finc_data_new ( FinCType* p_type, ADT p_ref )
{
    FinCData * self;

    self = (FinCData*)mem_new(sizeof(FinCData));
    object_init_object ( (Object*) self, finc_data_destroy );
    self->type = addref ( FinCType, p_type );
    self->pointer = NULL;
	self->vector_child = NULL;
	self->array_stand = 0;
    if ( p_ref )
    {
    	self->ref = TRUE;
    	self->raw = p_ref;
	    finc_data_init_data ( self, p_ref );

    	return self;
    }

    self->ref = FALSE;
    self->raw = NULL;
    finc_data_init_data ( self, NULL );

    return self;
}

FinCData* finc_data_new_data ( FinCType* p_type, ADT p_ref )
{
    FinCData * self;

	if (!p_ref) return NULL;

	self = (FinCData*)mem_new(sizeof(FinCData));
    object_init_object ( (Object*) self, finc_data_destroy );
    self->type = addref ( FinCType, p_type );
    self->pointer = NULL;
	self->vector_child = NULL;

	self->ref = FALSE;
	self->raw = p_ref;
	finc_data_init_data ( self, p_ref );

	return self;
}

/*
copy p_data to new data, but without its ref.
struct type:
*/
FinCData* finc_data_new_copy (FinCData* p_data)
{
	FinCData* self;

	self = finc_data_new (p_data->type, NULL);
	mem_copy(p_data->raw, self->raw, finc_type_get_size(p_data->type));

	if ( p_data->pointer )
	{
		self->pointer = addref(FinCData, p_data->pointer);
	}

	return self;
}

/*
use p_str to generate a string type data.
*/
FinCData* finc_data_new_string (unsigned char* p_str)
{
	FinCData* self;
	FinCData* l_str;
	FinCType* l_type;

	l_type = finc_type_new ( FinCType_String, FinCArrayType_None, 0);
	self = finc_data_new( l_type, NULL);
	unref(l_type);

	l_str = finc_data_new_raw_string (p_str);

	mem_copy(&l_str->raw, self->raw, sizeof(ADT));
	self->pointer = addref(FinCData, l_str);
	unref(l_str);

	return self;
}

/*
use p_str to generate a raw string data, it will copy p_str to new raw data.
*/
FinCData* finc_data_new_raw_string (unsigned char* p_str)
{
	FinCData* self;
	FinCType* l_type;
	int l_size;

	l_size = strlen(p_str)+1;

	l_type = finc_type_new (FinCType_Char, FinCArrayType_Fixed, l_size);
	self = finc_data_new( l_type, NULL);
	unref(l_type);

	mem_copy( p_str, self->raw, l_size);

	return self;
}

void finc_data_destroy ( Object* self )
{
	FinCData* l_self;
	FinCFunc* func;
	
	l_self = (FinCData*)self;
	
	unref(l_self->vector_child);

	if ( (l_self->type->type & FinCType_String)||(l_self->type->type & FinCType_Pointer) )
	{
		unref(l_self->pointer);
	}
	else if ( l_self->type->type & FinCType_Func )
	{

		func = (FinCFunc*)finc_access( l_self->raw, 0, ADT);
		unref(func);
	}

	if ( !l_self->ref ) mem_destroy(l_self->raw);

	l_self->raw = NULL;
	unref(l_self->type);

	mem_destroy ( l_self );
}

void finc_data_init_data ( ADT self, ADT data )
{
    FinCData* l_data;
    int i;
    unsigned int l_array;
    FinCStruct* l_struct;

    l_data = ( FinCData* ) self;

    if ( l_data->type->array_type == FinCArrayType_None )
        l_array = 1;
    else
        l_array = l_data->type->array_size;

    /*alloc new data block*/
	if ( data )
	{
		l_data->raw = data;
	}
    else
	{
		l_data->raw = (ADT) mem_new ( finc_type_get_size(l_data->type) );

		if (( l_data->type->type & FinCType_String )||( l_data->type->type & FinCType_Pointer ))
		{
			for ( i = 0; i < l_array; i++ )
				finc_access ( l_data->raw, i * sizeof( ADT ), unsigned char* ) = NULL;
		}
		else if ( l_data->type->type & FinCType_Int )
		{
			for ( i = 0; i < l_array; i++ )
				finc_access ( l_data->raw, i*sizeof(int), int ) = 0;
		}
		#ifdef USING_FLOAT
		else if ( l_data->type->type & FinCType_Float )
		{
			for ( i = 0; i < l_array; i++ )
				finc_access ( l_data->raw, i*sizeof(float), float ) = 0.0;
		}
		#endif
		else if ( l_data->type->type & FinCType_Bool )
		{
			for ( i = 0; i < l_array; i++ )
				finc_access ( l_data->raw, i*sizeof(Bool), Bool ) = FALSE;
		}
	}

	if ( l_data->type->type & FinCType_Struct )
	{
		l_struct = finc_context_get_struct (g_finc_context, l_data->type->name);
		l_data->vector_child = finc_struct_init_data(l_struct, l_data->raw);
		unref(l_struct);
	}
}

String* finc_data_get_string ( FinCData* self )
{
	String * l_text;

	l_text = string_new ();
	string_set_str ( l_text, finc_access ( self->raw, 0, char* ) );

	return l_text;
}

void finc_data_set_string ( FinCData* self, String* p_value )
{
	int l_size;
	FinCData* l_string;
	FinCType* l_type;

	l_size = string_get_size ( p_value )+1;
	l_type = finc_type_new(FinCType_Char, FinCArrayType_Fixed, l_size);
	l_string = finc_data_new(l_type, NULL);

	mem_copy ( string_get_str(p_value), l_string->raw, l_size);

	if(self->pointer)unref(self->pointer);
	self->pointer = addref(FinCData, l_string);

	self->raw = l_string->raw;
	unref(l_string);
}

void finc_data_assign ( FinCData* self, FinCData* p_src )
{
	FinCData* l_data;
	char l_str[ 1000 ];

	if ( !p_src )
	{
		printf ("Runtime Error: source data not available\n" );
		finc_context_error_inc( g_finc_context );
		return ;
	}

	if ( !self )
	{
		printf ("Runtime Error: destination data not available\n" );
		finc_context_error_inc( g_finc_context );
		return ;
	}

	if ( self->type->type & FinCType_String )
	{
		if ( p_src->type->type & FinCType_String )
		{
			if ( p_src->pointer )
			{
				l_data = finc_data_new_copy(p_src->pointer);
				unref(self->pointer);
				self->pointer = addref(FinCData, l_data);
				unref(l_data);
				mem_copy(&self->pointer->raw, self->raw, sizeof(ADT));
			}
			else
			{
				unref(self->pointer);
				self->pointer = NULL;
				mem_copy(p_src->raw, self->raw, sizeof(ADT));
			}
		}
		if ( p_src->type->type & FinCType_Int )
		{
			sprintf ( l_str, "%d", finc_access ( p_src->raw, 0, unsigned int ) );
			l_data = finc_data_new_string (l_str);
			unref(self->pointer);
			self->pointer = addref(FinCData, l_data->pointer);
			unref(l_data);
			mem_copy(&self->pointer->raw, self->raw, sizeof(ADT));
		}
		#ifdef USING_FLOAT
		if ( p_src->type->type & FinCType_Float )
		{
			sprintf ( l_str, "%f", finc_access ( p_src->raw, 0, float ) );
			l_data = finc_data_new_string (l_str);
			unref(self->pointer);
			self->pointer = addref(FinCData, l_data->pointer);
			unref(l_data);
			mem_copy(&self->pointer->raw, self->raw, sizeof(ADT));
		}
		#endif
		#ifdef USING_DOUBLE
		if ( p_src->type->type & FinCType_Double )
		{
			sprintf ( l_str, "%f", finc_access ( p_src->raw, 0, double ) );
			l_data = finc_data_new_string (l_str);
			unref(self->pointer);
			self->pointer = addref(FinCData, l_data->pointer);
			unref(l_data);
			mem_copy(&self->pointer->raw, self->raw, sizeof(ADT));
		}
		#endif
	}

	if ( self->type->type & FinCType_Char)
	{
		finc_access ( self->raw, 0, char ) = finc_access ( p_src->raw, 0, char );
	}

	if ( self->type->type & FinCType_Int )
	{
		finc_access ( self->raw, 0, int ) = finc_access ( p_src->raw, 0, int );
	}

	if ( self->type->type & FinCType_Short )
	{
		finc_access ( self->raw, 0, short ) = finc_access ( p_src->raw, 0, short );
	}

	#ifdef USING_FLOAT
	if ( self->type->type & FinCType_Float )
	{
		finc_access ( self->raw, 0, float ) = finc_access ( p_src->raw, 0, float );
	}
	#endif

	if ( self->type->type & FinCType_Pointer )
	{
		if ( p_src->pointer )
		{
			finc_data_set_pointer( self, p_src->pointer);
		}
		else
		{
			unref ( self->pointer );
			self->pointer = NULL;
			mem_copy(p_src->raw, self->raw, sizeof(ADT));
		}
	}

	if ( self->type->type & FinCType_Struct )
	{
		printf("not implement yet!\n");
	}
}

/*
used by array data type
*/
FinCData* finc_data_get_index ( FinCData* self, int p_index )
{
	FinCData * l_data;
	FinCType* l_type;

	if (self->type->type & FinCType_Pointer) return NULL; /* do not support get offset of pointer */

	if (self->type->type & FinCType_String)
	{
		if (self->type->array_type != FinCArrayType_None)
		{
		/*
		    l_type = finc_type_new(FinCType_String, FinCArrayType_None, 0 );
	    	l_data = finc_data_new(l_type, &finc_access(self->raw, p_index * sizeof(ADT), ADT));
			unref(l_type);
		*/
			return NULL;
		}
		else
		{
		    l_type = finc_type_new(FinCType_Char, FinCArrayType_None, 0 );
		    l_data = finc_data_new(l_type, &(((char*)finc_access(self->raw, 0, ADT))[p_index]));
			unref(l_type);
		}
	}
	else
	{
	    l_type = finc_type_new(self->type->type, FinCArrayType_None, 0 );
	    l_data = finc_data_new(l_type, &finc_access(self->raw, p_index * sizeof(ADT), ADT));
	    unref(l_type);
	}

	return l_data;
}

void finc_data_set_pointer ( FinCData* self, FinCData* p_raw )
{
    if ( !self )
    {
		printf("Runtime Error: pointer source data unavailable.\n");
		finc_context_error_inc( g_finc_context );
		return;
    }
    
    if(self->pointer)unref(self->pointer);
    
    if (p_raw)
    {
		self->pointer = addref(FinCData, p_raw);
		mem_copy(&p_raw->raw, self->raw, sizeof(ADT));
    }
    else self->pointer = NULL;
}

FinCData* finc_data_get_field (FinCData* self, int p_index)
{
    if (!self) return NULL;
    if (!( self->type->type & FinCType_Struct )) return NULL; 
    
    return vector_at(self->vector_child, p_index);
}
