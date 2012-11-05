#include <finc/fincnode.h>
#include <finc/finccontext.h>
#include <finc/finctype.h>
#include <finc/finclib.h>

FinCNode* finc_node_new ()
{
    FinCNode *self;
    
    self = (FinCNode*)mem_new(sizeof(FinCNode));
    object_init_object (OBJECT (self), finc_node_destroy);
    
    self->node_type = FinCNodeType_None;
    self->data = NULL;
    self->func = NULL;
    self->type = NULL;
    self->identifier = NULL;
    self->source_file = NULL;
    self->source_line = 0;
    self->check = TRUE;
    self->constant = FALSE;
    
    self->vector_node = vector_new ();
    
    return self;
}

FinCNode* finc_node_new_func ( unsigned char* p_name)
{
	FinCNode* self;
	String*	l_name;

	self = finc_node_new ();
	l_name = string_new_str ( p_name );
	finc_node_set_func (self, l_name);
	unref (l_name);

	return self;
}

FinCNode* finc_node_new_name ( unsigned char* p_name)
{
	FinCNode* self;
	String*	l_name;

	self = finc_node_new ();
	l_name = string_new ();
	string_set_str (l_name, p_name);
	finc_node_set_identifier (self, l_name);
	unref (l_name);

	return self;
}

FinCNode* finc_node_new_type (String* p_typename, FinCArrayType p_array, unsigned int p_size)
{
	FinCNode* l_node;
	FinCType* l_type;

	l_type = finc_type_new_name ( string_get_str (p_typename), p_array, p_size);
	l_node = finc_node_new ();

	finc_node_set_type (l_node, l_type);
	unref (l_type);

	return l_node;
}

FinCNode* finc_node_new_char (unsigned char p_char)
{
	FinCNode* l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_type = finc_type_new (FinCType_Char, FinCArrayType_None, 0);
	l_data = finc_data_new (l_type, NULL);
	finc_access (l_data->raw, 0, char) = p_char;

	l_node = finc_node_new ();
	finc_node_set_constant (l_node);
	finc_node_set_data (l_node, l_data);

	unref (l_type);
	unref (l_data);

	return l_node;
}

FinCNode* finc_node_new_string (unsigned char* p_text)
{
	FinCNode* l_node;
	FinCData* l_data;

	l_data = finc_data_new_string (p_text);

	l_node = finc_node_new ();
	finc_node_set_constant (l_node);
	finc_node_set_data (l_node, l_data);

	unref (l_data);

	return l_node;
}

FinCNode* finc_node_new_integer (unsigned int p_int)
{
	FinCNode* l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_type = finc_type_new (FinCType_Int, FinCArrayType_None, 0);
	l_data = finc_data_new (l_type, NULL);
	finc_access (l_data->raw, 0, int) = p_int;

	l_node = finc_node_new ();
	finc_node_set_constant (l_node);
	finc_node_set_data (l_node, l_data);

	unref (l_type);
	unref (l_data);

	return l_node;
}

#ifdef USING_FLOAT
FinCNode* finc_node_new_float (float p_value)
{
	FinCNode* l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_type = finc_type_new (FinCType_Float, FinCArrayType_None, 0);
	l_data = finc_data_new (l_type, NULL);
	finc_access (l_data->raw, 0, float) = p_value;

	l_node = finc_node_new ();
	finc_node_set_constant (l_node);
	finc_node_set_data (l_node, l_data);

	unref (l_type);
	unref (l_data);

	return l_node;
}
#endif

#ifdef USING_DOUBLE
FinCNode* finc_node_new_double (double p_value)
{
	FinCNode* l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_type = finc_type_new (FinCType_Float, FinCArrayType_None, 0);
	l_data = finc_data_new (l_type, NULL);
	finc_access (finc_data_get_raw_data (l_data), 0, double) = p_value;

	l_node = finc_node_new ();
	finc_node_set_constant (l_node);
	finc_node_set_data (l_node, l_data);

	unref (l_type);
	unref (l_data);

	return l_node;
}
#endif

FinCNode* finc_node_new_long (long p_long)
{
	FinCNode* l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_type = finc_type_new (FinCType_Float, FinCArrayType_None, 0);
	l_data = finc_data_new (l_type, NULL);
	finc_access (finc_data_get_raw_data (l_data), 0, float) = p_long;

	l_node = finc_node_new ();
	finc_node_set_constant (l_node);
	finc_node_set_data (l_node, l_data);

	unref (l_type);
	unref (l_data);

	return l_node;
}

FinCNode* finc_node_new_bool (Bool p_bool)
{
	FinCNode* l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_type = finc_type_new (FinCType_Bool, FinCArrayType_None, 0);
	l_data = finc_data_new (l_type, NULL);
	finc_access (finc_data_get_raw_data (l_data), 0, Bool) = p_bool;

	l_node = finc_node_new ();
	finc_node_set_constant (l_node);
	finc_node_set_data (l_node, l_data);

	unref (l_type);
	unref (l_data);

	return l_node;
}

FinCNode* finc_node_new_pointer (void* p_ptr)
{
	FinCNode* l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_type = finc_type_new (FinCType_Pointer, FinCArrayType_None, 0);
	l_data = finc_data_new (l_type, NULL);
	finc_access (finc_data_get_raw_data (l_data), 0, void*) = p_ptr;

	l_node = finc_node_new ();
	finc_node_set_constant (l_node);
	finc_node_set_data (l_node, l_data);

	unref (l_type);
	unref (l_data);

	return l_node;
}

void finc_node_destroy (Object* self)
{
    if (((FinCNode*)self)->data)
    {
	if (((Object*)((FinCNode*)self)->data)->refcount ==1)
	{
	    unref ( ((FinCNode*)self)->data);
	    ((FinCNode*)self)->data = NULL;
	}
	else 
	{
	    unref ( ((FinCNode*)self)->data);
	}
    }
    unref ( ((FinCNode*)self)->func);
    unref ( ((FinCNode*)self)->type);
    unref ( ((FinCNode*)self)->identifier);
    unref ( ((FinCNode*)self)->vector_node);
    
    mem_destroy (self);
}

void finc_node_evaluate (FinCNode* self)
{
	FinCNode* l_subnode;
	FinCData* l_data;
	FinCVar*  l_var;
	FinCFunc* func;
	FinCType* type;
	unsigned int i, l_size;

	if (!self)return;
	if ( g_finc_context->script_continue ||
		g_finc_context->script_break ||
		g_finc_context->script_return )
		return ;

	switch (self->node_type)
	{
	case FinCNodeType_None:
		break;
	case FinCNodeType_Block:
		l_size = vector_get_size (self->vector_node);
		for (i = 0; i < l_size; i++)
		{
			l_subnode = (FinCNode*) vector_at (self->vector_node, i);
			finc_node_evaluate (l_subnode);
			unref (l_subnode);
		}
		break;
	case FinCNodeType_Data:
		break;
	case FinCNodeType_Identifier:
		l_var = finc_context_get_var (g_finc_context, self->identifier);
		if (l_var)
		{
			unref (self->data);
			self->data = addref (FinCData, l_var->data);
			unref (l_var);
		}
		else
		{
			func = finc_context_get_func (g_finc_context, self->identifier);
			if ( func )
			{
				type = finc_type_new(FinCType_Func, FinCArrayType_None, 0);
				l_data = finc_data_new(type, NULL);
				unref(type);

				finc_access(finc_data_get_raw_data(l_data), 0, ADT) = func;

				unref(self->data);
				self->data = l_data;
			}
			else
			{
				printf ("Runtime Error: variable '%s' not founded\n", string_get_str (self->identifier));
				finc_context_error_inc( g_finc_context );
			}
		}
		break;
	case FinCNodeType_Func:
		if (!(self->func))self->func = finc_context_get_func (g_finc_context, self->identifier);

		if (self->func)
		{
			unref (self->data);
			self->data = NULL;

			l_data = finc_func_call (self->func, self);
			if (l_data) self->data = addref (FinCData, l_data);

			unref (l_data);
		}
		else
		{
			l_var = finc_context_get_var( g_finc_context, self->identifier);
			if ( l_var )
			{
				func = (FinCFunc*)finc_access(l_var->data->raw, 0, ADT);
				l_data = finc_func_call ( func, self);
				if (l_data) self->data = addref( FinCData, l_data );

				unref(l_data);
				unref(l_var);
			}
			else
			{
				printf ("Runtime Error: function '%s' not founded\n", string_get_str (self->identifier));
				finc_context_error_inc( g_finc_context );
			}
		}

		break;
	default:
		break;
	}
}

void finc_node_set_data (FinCNode* self, FinCData* p_data)
{
	self->node_type = FinCNodeType_Data;

	unref (self->data);
	self->data = addref (FinCData, p_data);
}

FinCData* finc_node_take_data (FinCNode* self)
{
    FinCData* l_data;
    
    if ( self->constant )
    {
		l_data = finc_data_new_copy(self->data);
    }
    else
    {
		l_data = self->data;
		self->data = NULL;
    }
    
    return l_data;
}

void finc_node_set_func (FinCNode* self, String* p_name)
{
    self->node_type = FinCNodeType_Func;

    unref (self->identifier);
    self->identifier = addref (String, p_name);
}

void finc_node_set_type (FinCNode* self, FinCType* p_type)
{
    self->node_type = FinCNodeType_Type;
    
    unref (self->type);
    self->type = addref (FinCType, p_type);
}

void finc_node_set_identifier (FinCNode* self, String* p_identifier)
{
    self->node_type = FinCNodeType_Identifier;
    
    unref (self->identifier);
    self->identifier = addref (String, p_identifier);
}
