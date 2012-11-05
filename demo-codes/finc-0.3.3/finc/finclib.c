#include <finc/finclib.h>
#include <finc/fincsys.h>

#define	HERE	kprintf("here, %s:%d\n", __FILE__, __LINE__)

FinC* finc_init()
{
    FinC* self;

    self = (FinC*)mem_new(sizeof(FinC));

    self->env = finc_lang_new();
    self->sys_func = finc_sys_new();
    self->context = finc_context_new();

    g_finc_context = self->context;
    g_finc_lang_env = self->env;

    finc_sys_init(self->sys_func);
    return self;
}

void finc_exit(FinC* self)
{
    unref(self->env);
    unref(self->sys_func);
    unref(self->context);

    mem_destroy(self);
}

void finc_insert_var(FinC* self, unsigned char* type, unsigned char* name, ADT data)
{
    FinCType* l_type;
    FinCVar* l_var;
    String* l_name;
    FinCData* l_data;

    l_name = string_new_str(name);
    l_var = finc_context_get_var(g_finc_context, l_name);
    if ( l_var )
    {
		printf("Error: can't insert variable for %s, the variable already exist in environment.\n", name);
		unref(l_var);
		unref(l_name);
		return;
    }
    else
    {
		l_type = finc_type_new_name(type, FinCArrayType_None, 0);
		l_data = finc_data_new (l_type, data);

		l_var = finc_var_new (l_name, l_data);
		finc_context_add_var(g_finc_context, l_var, TRUE);
		unref(l_type);
		unref(l_var);
		unref(l_data);
		unref(l_name);
    }
}

void finc_remove_var(FinC* self, unsigned char* name)
{
}

ADT finc_get_var(FinC* self, unsigned char* name)
{
    ADT result;
    FinCVar* l_var;
    String* l_name;

    result = NULL;
    l_name = string_new_str (name);
    l_var = finc_context_get_var(g_finc_context, l_name);

    if (l_var)
    {
		result = l_var->data->raw;
		unref(l_var);
    }

    unref(l_name);
    return result;
}

void finc_insert_sys_api(FinC* self, unsigned char* p_name, void* p_func, unsigned char* p_rettype)
{
    FinCFunc* l_func;

    l_func = finc_context_add_func_sys_api (g_finc_context, p_name, p_func);
    l_func->ret_type = finc_type_new_name (p_rettype, FinCArrayType_None, 0);
}

void finc_insert_func(FinC* self, unsigned char* p_name, void* p_func, unsigned char* p_rettype, ...)
{
    va_list lst;
    FinCFunc* l_func;
    FinCField* l_field;
    FinCType* l_type;
    String* l_name;
    unsigned char* l_paramtype;
    unsigned char* l_paramname;

    l_func = finc_context_add_func_native (g_finc_context, p_name, p_func);
    l_func->ret_type = finc_type_new_name (p_rettype, FinCArrayType_None, 0);

    va_start (lst, p_rettype);
    l_paramtype = va_arg(lst, unsigned char*);
    while (l_paramtype)
    {
		if (strcmp (l_paramtype, "...") == 0)
		{
			l_func->opt_param = TRUE;
		}
		else
		{
			l_paramname = va_arg (lst, unsigned char*);

			l_type = finc_type_new_name (l_paramtype, FinCArrayType_None, 0);
			l_name = string_new_str ( l_paramname);

			l_field = finc_field_new (l_name, l_type);
			unref (l_type);
			unref (l_name);

			finc_func_add_param (l_func, l_field);
			unref (l_field);
		}

		l_paramtype = va_arg(lst, unsigned char*);
    }

    va_end (lst);
}

ADT finc_call_func(FinC* self, unsigned char* func)
{
    return NULL;
}

void finc_proc_method_table(FinC* self, FinCMethodTable table, int size)
{
	int i;
	for ( i=0; i<size; i++)
	{
		finc_insert_func(self, table[i].method_name, table[i].method_ptr, "void", "void", NULL);
	}
}

#ifdef USING_FILE
void finc_run_script(FinC* self, unsigned char* filename)
{
    FinCNode* l_node;
    FinCFunc* l_func;
    String* l_name;
    FinCData* data_return;
    FinCParser* parser;

    parser = finc_parser_new();
    finc_parser_set_env(parser, self->env);

    finc_parser_parser_file(parser, filename);
    l_node =  addref(FinCNode, parser->tree_root);

    unref(parser);

    if (l_node)
    {
		finc_node_evaluate (l_node);
		unref (l_node);
	
		if ( g_finc_context->error != 0 )
		{
		    printf("\t%d error founded.\n", g_finc_context->error);
		    return ;
		}
		else
		{
		    l_name = string_new ();
		    string_set_str (l_name, "main");
		    l_func = finc_context_get_func (g_finc_context, l_name);
		    unref (l_name);
		    if (l_func)
		    {
				data_return = finc_func_call (l_func, NULL);
				unref (l_func);
				unref (data_return);
		    }
		    else
		    {
				printf ("Runtime Error:function 'main' not founded\n");
				finc_context_error_inc( g_finc_context );
		    }
		}
    }
}
#endif

void finc_run_string(FinC* self, unsigned char* str)
{
    FinCNode* l_node;
    String* l_str;
    FinCParser* parser;

    parser = finc_parser_new();
    finc_parser_set_env(parser, self->env);
    l_str = string_new_str(str);
	
	finc_parser_parser_string(parser, l_str);
    l_node =  addref(FinCNode, parser->tree_root);
    unref(parser);

    if ( g_finc_context->error !=0 )
    {
		printf("\t%d error founded, stopped...\n", g_finc_context->error);
		unref(l_node);
		return;
    }

    if (l_node)
    {
		finc_node_evaluate (l_node);
		unref (l_node);
    }
}
