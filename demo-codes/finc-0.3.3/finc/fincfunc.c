#include <finc/fincfunc.h>
#include <finc/finccontext.h>
#include <finc/finclang.h>
#include <finc/finclib.h>
#include "avcall/avcall.h"

void* (* finc_func_sys_api) (Vector* param);

FinCData* g_finc_func_return = NULL;

FinCFunc* finc_func_new ()
{
	FinCFunc *self;

	self = (FinCFunc*)mem_new(sizeof(FinCFunc));
	object_init_object (OBJECT (self), finc_func_destroy);

	self->type = FinCFuncType_None;
	self->node = NULL;
	self->ret_type = NULL;
	self->name = string_new ();
	self->vector_params = vector_new ();
	self->opt_param = FALSE;

	return self;
}

void finc_func_destroy (Object* self)
{
	unref ( ((FinCFunc*)self)->node);
	unref ( ((FinCFunc*)self)->name);
	unref ( ((FinCFunc*)self)->ret_type);
	unref ( ((FinCFunc*)self)->vector_params);

	mem_destroy (self);
}

void finc_func_set_sys (FinCFunc* self, String* p_name, FinCFuncSys p_sys)
{
	self->type = FinCFuncType_Sys;
	self->sys = p_sys;

	unref (self->name);
	self->name = addref (String, p_name);
}

void finc_func_set_sys_api (FinCFunc* self, String* p_name, ADT sys_api)
{
	self->type = FinCFuncType_Sys_Api;
	self->native = sys_api;

	unref(self->name);
	self->name = addref(String, p_name);
}

void finc_func_set_native (FinCFunc* self, String* p_name, ADT p_native)
{
	self->type = FinCFuncType_Native;
	self->native = p_native;

	unref (self->name);
	self->name = addref (String, p_name);
}

void finc_func_set_node (FinCFunc* self, String* p_name, FinCNode* p_node)
{
	self->type = FinCFuncType_Node;

	unref (self->name);
	self->name = addref (String, p_name);

	unref (self->node);
	self->node = addref (FinCNode, p_node);
}

void finc_func_add_param (FinCFunc* self, FinCField* p_param)
{
	vector_append (self->vector_params, (Object*) p_param);
}

FinCData* finc_func_call (FinCFunc* self, FinCNode* p_node)
{
	HashTable* l_context;
	FinCVar* l_var;
	FinCData* l_data;
	FinCData* l_return;
	FinCData* l_node_data;
	FinCNode* l_node;
	FinCField* l_field;
	Vector* vector_param;
	String* l_name;
	int l_size;
	int i;

	switch (self->type)
	{
	case FinCFuncType_Sys:/*language system function*/
	    (*(self->sys)) (p_node);
	    return p_node->data;

	case FinCFuncType_Native:/*native function*/
		return finc_func_native_call(self, p_node);

	case FinCFuncType_Sys_Api:
	    l_size = vector_get_size (p_node->vector_node);

	    vector_param = vector_new();
	    for (i=0; i<l_size; i++)
	    {
			l_node =  (FinCNode*) vector_at (p_node->vector_node, i);
			finc_node_evaluate (l_node);
			vector_append(vector_param, l_node->data);
			unref (l_node);
	    }
	    
	    finc_func_sys_api = self->native;
	    l_data = (*finc_func_sys_api)(vector_param);

	    unref(vector_param);
	    return l_data;

	case FinCFuncType_Node:/*FinC script function*/
	    if (p_node)
	    {
			l_size = vector_get_size (self->vector_params);
			for (i=0; i<l_size; i++)
			{
				l_node =  (FinCNode*) vector_at (p_node->vector_node, i);
				finc_node_evaluate (l_node);
				unref (l_node);
			}
	    }
	    l_context = finc_context_func_enter (g_finc_context);

	    if (p_node)
	    {
			l_size = vector_get_size (self->vector_params);
			
			for (i=0; i<l_size; i++)
			{
				l_field = (FinCField*) vector_at (self->vector_params, i);
				l_node =  (FinCNode*) vector_at (p_node->vector_node, i);
				
				l_name = l_field->name;
				l_node_data = finc_node_take_data(l_node);
				l_var = finc_var_new_copy (l_name, l_node_data);
				
				finc_context_add_var (g_finc_context, l_var, FALSE);
				
				unref (l_field);
				unref (l_node);
				unref (l_node_data);
				unref (l_var);
			}
	    }
	    
	    g_finc_context->script_return = FALSE;
	    finc_node_evaluate (self->node);/*execute function body!*/
	    g_finc_context->script_return = FALSE;
	    
	    finc_context_func_leave (g_finc_context, l_context);
	    
	    l_return = g_finc_func_return;
	    g_finc_func_return = NULL;
	    return l_return;

		default:
			break;
	}

	return NULL;
}

FinCData* finc_func_native_call (FinCFunc* self, FinCNode* node)
{
    FinCField* field;
    FinCNode* child_node;
    FinCData* return_data;
    int args_size;
    int i;
    av_alist av;
	ADT ret_p;

    if(!self) return NULL;

    return_data = finc_data_new (self->ret_type, NULL);
    switch (self->ret_type->type)
    {
    case FinCType_Void:
		av_start_void(av, self->native);
		break;
    case FinCType_Char:
		av_start_char(av, self->native, return_data->raw);
		break;
    case FinCType_Short:
		av_start_short(av, self->native, return_data->raw);
		break;
    case FinCType_Int:
		av_start_int(av, self->native, return_data->raw);
		break;
    case FinCType_Bool:
		av_start_short(av, self->native, return_data->raw);
		break;
	#ifdef USING_FLOAT
    case FinCType_Float:
		av_start_float(av, self->native, return_data->raw);
		break;
	#endif
	#ifdef USING_FLOAT
    case FinCType_Double:
		av_start_double(av, self->native, return_data->raw);
		break;
	#endif
    case FinCType_Pointer:
    case FinCType_String:
		/*av_start_ptr(av, self->native, ADT, return_data->raw);*/
		av_start_ptr(av, self->native, ADT, &ret_p);
		break;
    case FinCType_Struct:
		/*av_start_struct(av, self->native, return_data->raw);*/
		break;
	default:
		return NULL;
    }
    
    args_size = vector_get_size (node->vector_node);
    for (i=0; i<args_size; i++)
    {
		field = (FinCField*) vector_at (self->vector_params, i);
		child_node =  (FinCNode*) vector_at (node->vector_node, i);
		finc_node_evaluate (child_node);
		
		if (child_node->data)
		{
			switch (child_node->data->type->type)
			{
			case FinCType_Char:
				av_char(av, finc_access(child_node->data->raw, 0, char));
				break;
			case FinCType_Short:
				av_short(av, finc_access(child_node->data->raw, 0, short));
				break;
			case FinCType_Int:
				av_int(av, finc_access(child_node->data->raw, 0, int));
				break;
			case FinCType_Bool:
				av_short(av, finc_access(child_node->data->raw, 0, short));
				break;
			#ifdef USING_FLOAT
			case FinCType_Float:
				av_float(av, finc_access(child_node->data->raw, 0, float));
				break;
			#endif
			#ifdef USING_DOUBLE
			case FinCType_Double:
				av_double(av, finc_access(child_node->data->raw, 0, double));
				break;
			#endif
			case FinCType_Pointer:
			case FinCType_String:
				av_ptr(av, ADT, finc_access(child_node->data->raw, 0, ADT));
				break;
			case FinCType_Struct:
				/*av_struct(av, finc_access(child_node->data->raw, 0, int));*/
				break;
			default :
				break;
			}
		}

		unref (field);
		unref (child_node);
    }

	if ( g_finc_context->error != 0 )
	{
		unref ( return_data );
		return NULL;
	}
	else av_call(av);

	if(self->ret_type->type == FinCType_String || self->ret_type->type == FinCType_Pointer)
	{
		finc_access(return_data->raw, 0, ADT) = ret_p;
	}
    return return_data;
}
