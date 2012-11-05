#include <finc/finclang.h>
#include <finc/fincstruct.h>
#include <finc/finccontext.h>
#include <finc/fincparser.h>

int g_lang_nberr=0;
FinCLangEnv* g_finc_lang_env=NULL;

FinCLangEnv* finc_lang_new()
{
    FinCLangEnv* self;
    
    self = (FinCLangEnv*)mem_new(sizeof(FinCLangEnv));
    
    self->tree_root = NULL;
    self->nb_error = 0;
    self->list_pkg = list_new();
    
#ifdef USING_PACKAGE
    self->libfactory = lib_factory_new();
#endif
    object_init_object((Object*)self, finc_lang_destroy);
    
    return self;
}

void finc_lang_destroy(Object* self)
{
    unref( ((FinCLangEnv*)self)->tree_root );
    unref( ((FinCLangEnv*)self)->list_pkg );
    
#ifdef USING_PACKAGE
    unref( ((FinCLangEnv*)self)->libfactory );
#endif
    
    mem_destroy(self);
}

void finc_lang_error_line (FinCTokenEnv* lex, char* msg)
{
    g_lang_nberr++;
    printf ("%d:%d: %s\n", lex->line, lex->position, msg);
}

Bool finc_lang_check_type (FinCLangEnv* self, String* p_type)
{
    FinCStruct* type;
    Bool result;
    
    type = finc_context_get_struct ( g_finc_context, p_type);
    result = type? TRUE: FALSE;
    unref(type);
    
    return result;
}

#ifdef USING_PACKAGE
void finc_lang_proc_pkg (FinCLangEnv* self, FinCNode* p_node)
{
    String* package_name;
    String* param_name;
    FinCNode* node_pkg;
    FinCNode* node_func;
    FinCNode* node_func_name;
    FinCNode* node_type;
    FinCNode* param_type;
    FinCNode* param;
    ADT func_handle;
    Library* lib;
    FinCFunc* func;
    FinCField* field;
    FinCType* type;
    int i, j;
    
    node_pkg = (FinCNode*)vector_at(p_node->vector_node, 0);
    package_name = addref(String, node_pkg->identifier);
    lib = lib_factory_load_lib(self->libfactory, string_get_str(package_name));
    
    for ( i=1; i<vector_get_size(p_node->vector_node); i++)
    {
	node_func = (FinCNode*)vector_at(p_node->vector_node, i);
	node_type = (FinCNode*)vector_at(node_func->vector_node, 0);
	node_func_name = (FinCNode*)vector_at(node_func->vector_node, 1);
	
	func_handle = library_symbol(lib, string_get_str(node_func_name->identifier));
	func = finc_context_add_func_native (g_finc_context,
					     string_get_str(node_func_name->identifier), func_handle);
	
	func->ret_type = finc_type_new_copy(node_type->type);
	for ( j=2; j<vector_get_size(node_func->vector_node); j+=2)
	{
	    param_type = (FinCNode*)vector_at(node_func->vector_node, j);
	    param = (FinCNode*)vector_at(node_func->vector_node, j+1);
	    
	    type = finc_type_new_copy(param_type->type);
	    param_name = string_new_str(string_get_str(param->identifier));
	    
	    field = finc_field_new(param_name, type);
	    finc_func_add_param(func, field);
	    
	    unref(param_type);
	    unref(param);
	    unref(type);
	    unref(param_name);
	    unref(field);
	}
	
	unref(node_func);
	unref(node_func_name);
	unref(node_type);
    }
    
    unref(package_name);
    unref(node_pkg);
    unref(lib);
}
#endif

#ifdef USING_FILE
void finc_lang_proc_import(FinCLangEnv* self, FinCNode* p_node)
{
    FinCNode* l_node;
    FinCData* l_data;
    String* l_text;
    String* temp;
    FinCParser* parser;
    
    l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
    finc_node_evaluate ( l_node );
    
    l_data = l_node->data;
    unref ( l_node );
    
    if ( l_data->type->type & FinCType_String )
    {
	l_text = finc_data_get_string ( l_data );
	temp = list_find(self->list_pkg, string_equal, (ADT)l_text);
	if (temp)/*already import this pacakge.*/
	{
	    unref(l_text);
	    unref(temp);
	    unref(l_data);
	    return;
	}
	else
	{
	    list_append(self->list_pkg, (ADT)l_text);
	}
	parser = finc_parser_new();
	
	finc_parser_set_env(parser, g_finc_lang_env);
	
	finc_parser_parser_file(parser, string_get_str(l_text));
	l_node =  addref(FinCNode, parser->tree_root);
	
	if ( l_node )
	{
	    finc_node_evaluate ( l_node );
	    unref ( l_node );
	}
	
	unref ( l_text );
	unref ( parser );
    }
    
    unref(l_data);
}
#endif

void finc_lang_proc_struct(FinCLangEnv* self, FinCNode* p_node)
{
    FinCStruct* l_struct;
    
    FinCNode* l_name;
    FinCNode* l_node_field;
    FinCNode* l_node_type;
    
    FinCField* l_field;
    FinCType* l_type;
    
    int i, j;
    
    l_name = (FinCNode*) vector_at(p_node->vector_node, 0);
    
    l_struct = finc_struct_new(l_name->identifier);
    
    for (i=1; i<finc_node_get_size(p_node); i++)
    {
	l_node_type = vector_at(p_node->vector_node, i);
	l_type = finc_type_new_copy (l_node_type->type);
	
	for (j=0; j<finc_node_get_size(l_node_type); j++)
	{
	    l_node_field = vector_at (l_node_type->vector_node, j);
	    l_field = finc_field_new(l_node_field->identifier, l_type);
	    finc_struct_add_field(l_struct, l_field);
	    
	    unref(l_node_field);
	    unref(l_field);
	}
	unref(l_type);
	unref(l_node_type);
    }
    
    finc_context_add_struct(g_finc_context, l_struct);
    
    unref(l_name);
    unref(l_struct);
}

void finc_lang_proc_func (FinCLangEnv* self, FinCNode* p_node )
{
    FinCFunc * l_func;
    FinCNode* l_node;
    String* l_function_name;
    FinCType* l_param_type;
    String* l_param_name;
    FinCField* l_field;
    FinCNode* l_code;
    unsigned int l_size;
    unsigned int i;
    
    l_size = finc_node_get_size ( p_node );
    
    l_node = finc_node_get ( p_node, 0 );
    if ( finc_node_check ( l_node, FinCNodeType_Type ) )unref ( l_node );
    else
    {
	printf("Runtime Error:function return type error.\n" );
	finc_context_error_inc( g_finc_context );
	unref ( l_node );
	return ;
    }
    
    l_node = finc_node_get ( p_node, 1 );
    if ( finc_node_check ( l_node, FinCNodeType_Identifier ) )
    {
	l_function_name = addref ( String, l_node->identifier );
	unref ( l_node );
    }
    else
    {
	printf("Runtime Error:function name error.\n");
	finc_context_error_inc( g_finc_context );
	unref ( l_node );
	return ;
    }
    
    l_code = finc_node_get ( p_node, l_size - 1 );
    l_func = finc_context_add_func_node ( g_finc_context, string_get_str ( l_function_name ), l_code );
    unref ( l_function_name );
    unref ( l_code );
    
    for ( i = 0; i < ( ( l_size - 3 ) / 2 ); i++ )
    {
	l_node = finc_node_get ( p_node, 2 + ( i * 2 ) );
	if ( finc_node_check ( l_node, FinCNodeType_Type ) )
	{
	    l_param_type = addref ( FinCType, l_node->type );
	    unref ( l_node );
	}
	else
	{
	    printf("func error");
	    unref ( l_node );
	    return ;
	}
	
	l_node = finc_node_get ( p_node, 2 + ( i * 2 ) + 1 );
	if ( finc_node_check ( l_node, FinCNodeType_Identifier ) )
	{
	    l_param_name = addref ( String, l_node->identifier );
	    unref ( l_node );
	}
	else
	{
	    printf("func error" );
	    unref ( l_node );
	    return ;
	}
	
	l_field = finc_field_new ( l_param_name, l_param_type );
	finc_func_add_param ( l_func, l_field );
	
	unref ( l_param_type );
	unref ( l_param_name );
	unref ( l_field );
    }
}
