#include <finc/fincsys.h>
#include <finc/finclang.h>
#include <finc/finccontext.h>
#include <finc/fincnode.h>
#include <finc/finclib.h>

#define FinC_ERROR printf

/* Declarators
 */
void finc_sys_global (FinCNode* p_node);
void finc_sys_local (FinCNode* p_node);

/* Low-level functions
 */
void finc_sys_addr_of (FinCNode* p_node);
void finc_sys_value_of (FinCNode* p_node);
void finc_sys_access (FinCNode* p_node);

/* Assignement
 */
void finc_sys_assign  (FinCNode* p_node);
void finc_sys_cast  (FinCNode* p_node);

/* Logic
 */
void finc_sys_logic_or (FinCNode* p_node);
void finc_sys_logic_and (FinCNode* p_node);

void finc_sys_not ( FinCNode* p_node );

void finc_sys_or (FinCNode* p_node);
void finc_sys_and (FinCNode* p_node);
void finc_sys_xor (FinCNode* p_node);
void finc_sys_bitwise (FinCNode* p_node);
void finc_sys_shl (FinCNode* p_node);
void finc_sys_shr (FinCNode* p_node);

/* Mathematics
 */
void finc_sys_add (FinCNode* p_node);
void finc_sys_sub (FinCNode* p_node);
void finc_sys_mul (FinCNode* p_node);
void finc_sys_div (FinCNode* p_node);
void finc_sys_mod (FinCNode* p_node);
void finc_sys_inc (FinCNode* p_node);
void finc_sys_dec (FinCNode* p_node);

void finc_sys_preinc (FinCNode* p_node);
void finc_sys_predec (FinCNode* p_node);

/* Flow control
 */
void finc_sys_block (FinCNode* p_node);
void finc_sys_if (FinCNode* p_node);
void finc_sys_for (FinCNode* p_node);
void finc_sys_while (FinCNode* p_node);
void finc_sys_return (FinCNode* p_node);
void finc_sys_break (FinCNode* p_node);
void finc_sys_continue (FinCNode* p_node);

/* Comparaisons
 */
void finc_sys_cmp_l (FinCNode* p_node);
void finc_sys_cmp_g (FinCNode* p_node);
void finc_sys_cmp_le (FinCNode* p_node);
void finc_sys_cmp_ge (FinCNode* p_node);
void finc_sys_cmp_ne (FinCNode* p_node);
void finc_sys_cmp_e (FinCNode* p_node);

/* Language control
 */
void finc_sys_import (FinCNode* p_node);
void finc_sys_array (FinCNode* p_node);
void finc_sys_condition (FinCNode* p_node);
void finc_sys_comma (FinCNode* p_node);

void finc_sys_negative( FinCNode* p_node );

FinCSys* finc_sys_new()
{
	FinCSys* self;

	self = (FinCSys*)mem_new(sizeof(FinCSys));

	self->env = NULL;

	object_init_object((Object*)self, finc_sys_destroy);

	return self;
}

void finc_sys_destroy(Object* self)
{
	unref( ((FinCSys*)self)->env );

	mem_destroy(self);
}

void finc_sys_init (FinCSys* self)
{
	/* Declarators
	 */
	finc_context_add_func_sys ( g_finc_context, "global", finc_sys_global );
	finc_context_add_func_sys ( g_finc_context, "local", finc_sys_local );

	finc_context_add_func_sys ( g_finc_context, "cast", finc_sys_cast );
	finc_context_add_func_sys ( g_finc_context, "addr_of", finc_sys_addr_of );
	finc_context_add_func_sys ( g_finc_context, "value_of", finc_sys_value_of );

	finc_context_add_func_sys ( g_finc_context, ".", finc_sys_access );

	finc_context_add_func_sys ( g_finc_context, "||", finc_sys_logic_or );
	finc_context_add_func_sys ( g_finc_context, "&&", finc_sys_logic_and );
	
	finc_context_add_func_sys ( g_finc_context, "!", finc_sys_not );

	finc_context_add_func_sys ( g_finc_context, "|", finc_sys_or );
	finc_context_add_func_sys ( g_finc_context, "&", finc_sys_and );
	finc_context_add_func_sys ( g_finc_context, "^", finc_sys_xor );
	finc_context_add_func_sys ( g_finc_context, "~", finc_sys_bitwise );

	finc_context_add_func_sys ( g_finc_context, "<<", finc_sys_shl );
	finc_context_add_func_sys ( g_finc_context, ">>", finc_sys_shr );

	finc_context_add_func_sys ( g_finc_context, ",", finc_sys_comma );
	finc_context_add_func_sys ( g_finc_context, "?", finc_sys_condition );

	finc_context_add_func_sys ( g_finc_context, "+", finc_sys_add );
	finc_context_add_func_sys ( g_finc_context, "-", finc_sys_sub );
	finc_context_add_func_sys ( g_finc_context, "*", finc_sys_mul );
	finc_context_add_func_sys ( g_finc_context, "/", finc_sys_div );
	finc_context_add_func_sys ( g_finc_context, "%", finc_sys_mod );

	finc_context_add_func_sys ( g_finc_context, "negative", finc_sys_negative );

	finc_context_add_func_sys ( g_finc_context, "++", finc_sys_inc );
	finc_context_add_func_sys ( g_finc_context, "--", finc_sys_dec );

	finc_context_add_func_sys ( g_finc_context, "preinc", finc_sys_preinc );
	finc_context_add_func_sys ( g_finc_context, "predec", finc_sys_predec );

	finc_context_add_func_sys ( g_finc_context, "[]", finc_sys_array );

	finc_context_add_func_sys ( g_finc_context, "if", finc_sys_if );
	finc_context_add_func_sys ( g_finc_context, "for", finc_sys_for );
	finc_context_add_func_sys ( g_finc_context, "while", finc_sys_while );
	finc_context_add_func_sys ( g_finc_context, "return", finc_sys_return );
	finc_context_add_func_sys ( g_finc_context, "continue", finc_sys_continue );
	finc_context_add_func_sys ( g_finc_context, "break", finc_sys_break );

	finc_context_add_func_sys ( g_finc_context, "<", finc_sys_cmp_l );
	finc_context_add_func_sys ( g_finc_context, ">", finc_sys_cmp_g );
	finc_context_add_func_sys ( g_finc_context, "<=", finc_sys_cmp_le );
	finc_context_add_func_sys ( g_finc_context, ">=", finc_sys_cmp_ge );
	finc_context_add_func_sys ( g_finc_context, "!=", finc_sys_cmp_ne );
	finc_context_add_func_sys ( g_finc_context, "==", finc_sys_cmp_e );

	finc_context_add_func_sys ( g_finc_context, "=", finc_sys_assign );

	finc_context_add_func_sys ( g_finc_context, "++", finc_sys_inc );
	finc_context_add_func_sys ( g_finc_context, "--", finc_sys_dec );

	finc_context_add_func_sys ( g_finc_context, "@", finc_sys_block );
}

void finc_sys_global ( FinCNode* p_node )
{
	FinCNode* l_node;
	FinCNode* node_var;
	FinCType* l_type;
	String* l_name;
	FinCData* l_data;
	FinCVar* l_var;
	FinCNode* l_init_node;
	int l_size, i;

	l_node = (FinCNode*) vector_at ( p_node->vector_node, 0 ) ;
	l_type = l_node->type;

	l_size = finc_node_get_size(l_node);

	for ( i=0; i<l_size; i++)
	{
		node_var = (FinCNode*) vector_at ( l_node->vector_node, i );
		l_name = node_var->identifier;

		l_data = finc_data_new ( l_type, NULL );
		if ( vector_get_size(node_var->vector_node)!=0 )//if has init node!
		{
			l_init_node = (FinCNode*) vector_at( node_var->vector_node, 0);
			finc_node_evaluate (l_init_node);
			finc_data_assign (l_data, l_init_node->data);
			unref(l_init_node);
		}
		unref ( node_var );

		l_var = finc_var_new ( l_name, l_data );

		finc_context_add_var ( g_finc_context, l_var, TRUE );

		unref ( l_data );
		unref ( l_var );
	}
	unref(l_node);
}

void finc_sys_local ( FinCNode* p_node )
{
	FinCNode* l_node;
	FinCNode* node_var;
	FinCType* l_type;
	String* l_name;
	FinCData* l_data;
	FinCVar* l_var;
	FinCNode* l_init_node;
	int l_size, i;

	l_node = (FinCNode*) vector_at ( p_node->vector_node, 0 ) ;
	l_type = l_node->type;

	l_size = finc_node_get_size(l_node);

	for ( i=0; i<l_size; i++)
	{
		node_var = (FinCNode*) vector_at ( l_node->vector_node, i );
		l_name = node_var->identifier;

		l_data = finc_data_new ( l_type, NULL );

		if ( vector_get_size(node_var->vector_node)!=0 )//if has init node!
		{
			l_init_node = (FinCNode*) vector_at( node_var->vector_node, 0);
			finc_node_evaluate (l_init_node);
			finc_data_assign (l_data, l_init_node->data);
			unref(l_init_node);
		}
		unref ( node_var );

		l_var = finc_var_new ( l_name, l_data );

		finc_context_add_var ( g_finc_context, l_var, FALSE );

		unref ( l_data );
		unref ( l_var );
	}
	unref(l_node);
}

void finc_sys_access ( FinCNode* p_node )
{
	FinCNode* l_main;
	FinCNode* l_sub;

	FinCData* l_data;
	FinCData* l_field;

	FinCStruct* l_struct;
	int l_index;

	l_main = (FinCNode*) vector_at (p_node->vector_node, 0);
	l_sub  = (FinCNode*) vector_at (p_node->vector_node, 1);

	finc_node_evaluate (l_main);

	if (!finc_node_check (l_sub, FinCNodeType_Identifier))
	{
		printf("Error:struct access, right must be a identifer!\n");
		unref(l_main);
		unref(l_sub);
		return;
	}

	l_data = addref(FinCData, l_main->data);
	if (!l_data)
	{
		printf("Runtime Error:struct variable not founded.\n");
		finc_context_error_inc( g_finc_context );
		unref(l_main);
		unref(l_sub);
		return;
	}
	l_struct = finc_context_get_struct (g_finc_context, l_data->type->name);
	l_index = finc_struct_get_field_index (l_struct, l_sub->identifier);
	l_field = finc_data_get_field(l_data, l_index);

	p_node->data = addref(FinCData, l_field);

	unref(l_main);
	unref(l_sub);
	unref(l_data);
	unref(l_field);
	unref(l_struct);
}

void finc_sys_array ( FinCNode* p_node )
{
	FinCNode * l_node;

	FinCData* l_data;
	FinCData* l_index;
	int index;

	l_node = (FinCNode*) vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );
	l_data = addref ( FinCData, l_node->data );
	unref ( l_node );

	l_node = (FinCNode*) vector_at ( p_node->vector_node, 1 );
	finc_node_evaluate ( l_node );
	l_index = addref ( FinCData, l_node->data );
	unref ( l_node );

	index = finc_access(l_index->raw, 0, int);

	if ( (index<0) || (index>(l_data->type->array_size-1)) )
	{
		printf("Runtime Error: array out of range.\n");
		finc_context_error_inc( g_finc_context );
		unref(l_data);
		unref(l_index);
		return;
	}

	unref ( p_node->data );
	p_node->data = finc_data_get_index ( l_data, index );
	l_data->array_stand = index;

	unref ( l_data );
	unref ( l_index );
}

void finc_sys_assign ( FinCNode* p_node )
{
	FinCNode * l_node;
	FinCData* l_src;
	FinCData* l_dst;

	l_node = FinC_NODE ( vector_at ( p_node->vector_node, 0 ) );
	finc_node_evaluate ( l_node );
	l_dst = finc_node_take_data(l_node);
	unref ( l_node );

	l_node = FinC_NODE ( vector_at ( p_node->vector_node, 1 ) );
	finc_node_evaluate ( l_node );
	l_src = finc_node_take_data(l_node);

	if ( l_node->node_type ==FinCNodeType_Func )
	{
		if (strcmp(string_get_str(l_node->identifier), "cast") ==0 ||
			strcmp(string_get_str(l_node->identifier), "contentof") == 0 )
		/*that is variable alias*/
		{
			l_dst = addref(FinCData, l_src);
		}
		else
		{
			finc_data_assign ( l_dst, l_src );
		}
	}
	else
	{
		finc_data_assign ( l_dst, l_src );
	}

	unref ( p_node->data );
	p_node->data = l_src;

	unref ( l_node );
	unref ( l_dst );
}

void finc_sys_cast ( FinCNode* p_node )
{
	FinCNode* l_type_node;
	FinCNode* l_data_node;
	FinCData* l_data;

	l_type_node = (FinCNode*) vector_at ( p_node->vector_node, 0 );
	l_data_node = (FinCNode*) vector_at ( p_node->vector_node, 1 );
	finc_node_evaluate ( l_data_node );

	l_data = finc_data_new ( l_type_node->type, l_data_node->data->raw );
	unref ( l_type_node );
	unref ( l_data_node );

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_addr_of ( FinCNode* p_node )
{
	FinCNode * l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_type = finc_type_new ( FinCType_Pointer, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	l_node = (FinCNode*) vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );

	finc_data_set_pointer (l_data, l_node->data);

	unref ( l_node );

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_value_of( FinCNode* p_node)
{
	FinCNode * l_node;

	l_node = (FinCNode*) vector_at (p_node->vector_node, 0);
	finc_node_evaluate (l_node);

	unref (p_node->data);
	p_node->data = addref( FinCData,  l_node->data->pointer );
	unref (l_node);
}

void finc_sys_if ( FinCNode* p_node )
{
	FinCNode * l_test;
	FinCNode* l_true;
	FinCNode* l_false;
	FinCData* l_data_test;

	l_test = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_true = (FinCNode*)vector_at ( p_node->vector_node, 1 );
	l_false = (FinCNode*)vector_at ( p_node->vector_node, 2 );

	finc_node_evaluate ( l_test );
	l_data_test = finc_node_take_data(l_test);

	if ( finc_access ( finc_data_get_raw_data ( l_data_test ), 0, Bool ) )
	{
		finc_node_evaluate ( l_true );
	}
	else
	{
		if ( l_false ) finc_node_evaluate ( l_false );
	}

	unref ( l_test );
	unref ( l_data_test );
	unref ( l_true );
	unref ( l_false );
}

void finc_sys_for ( FinCNode* p_node )
{
	FinCNode * node1;
	FinCNode* node2;
	FinCNode* node3;
	FinCNode* code;
	Bool old_continue, old_break, old_in_cycle;

	node1 = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	node2 = (FinCNode*)vector_at ( p_node->vector_node, 1 );
	node3 = (FinCNode*)vector_at ( p_node->vector_node, 2 );

	code = (FinCNode*)vector_at ( p_node->vector_node, 3 );

	finc_node_evaluate ( node1 );
	finc_node_evaluate ( node2 );

	old_continue = g_finc_context->script_continue;
	old_break = g_finc_context->script_break;
	old_in_cycle = g_finc_context->script_in_cycle;

	while ( finc_access ( finc_data_get_raw_data ( node2->data ), 0, Bool ) )
	{
		g_finc_context->script_in_cycle = TRUE;
		finc_node_evaluate ( code );
		if (g_finc_context->script_break)
		{
			g_finc_context->script_break = FALSE;
			g_finc_context->script_in_cycle = FALSE;
			break;
		}
		g_finc_context->script_continue = FALSE;
		finc_node_evaluate ( node3 );
		finc_node_evaluate ( node2 );
		g_finc_context->script_in_cycle = FALSE;
	}

	unref ( node1 );
	unref ( node2 );
	unref ( node3 );
	unref ( code );

	g_finc_context->script_continue = old_continue;
	g_finc_context->script_break = old_break;
	g_finc_context->script_in_cycle = old_in_cycle;
}

void finc_sys_while ( FinCNode* p_node )
{
	FinCNode * l_test;
	FinCNode* l_code;
	Bool old_continue, old_break, old_in_cycle;

	l_test = FinC_NODE ( vector_at ( p_node->vector_node, 0 ) );
	l_code = FinC_NODE ( vector_at ( p_node->vector_node, 1 ) );

	finc_node_evaluate ( l_test );

	old_continue = g_finc_context->script_continue;
	old_break = g_finc_context->script_break;
	old_in_cycle = g_finc_context->script_in_cycle;

	while ( finc_access ( finc_data_get_raw_data ( l_test->data ), 0, Bool ) )
	{
		g_finc_context->script_in_cycle = TRUE;
		finc_node_evaluate ( l_code );
		if (g_finc_context->script_break)
		{
			g_finc_context->script_break = FALSE;
			g_finc_context->script_in_cycle = FALSE;
			break;
		}
		g_finc_context->script_continue = FALSE;
		finc_node_evaluate ( l_test );
		g_finc_context->script_in_cycle = FALSE;
	}

	unref ( l_test );
	unref ( l_code );
	g_finc_context->script_continue = old_continue;
	g_finc_context->script_break = old_break;
	g_finc_context->script_in_cycle = old_in_cycle;
}

void finc_sys_return ( FinCNode* p_node )
{
	FinCNode * l_node;

	l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );

	if (l_node)	g_finc_func_return = addref ( FinCData, l_node->data );
	else g_finc_func_return = NULL;

	unref ( l_node );

	g_finc_context->script_return = TRUE;
}

void finc_sys_continue ( FinCNode* p_node )
{
	if ( g_finc_context->script_in_cycle )
	{
		g_finc_context->script_continue = TRUE;
		return;
	}
	printf("Runtime Error: can't use continue not in a cycle.\n");
	finc_context_error_inc( g_finc_context );
}

void finc_sys_break ( FinCNode* p_node )
{
	if ( g_finc_context->script_in_cycle )
	{
		g_finc_context->script_break = TRUE;
		return;
	}
	printf("Runtime Error: can't use break not in a cycle.\n");
	finc_context_error_inc( g_finc_context );
}

void finc_sys_preinc ( FinCNode* p_node)
{
	FinCNode * l_node;

	l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );

	finc_access ( finc_data_get_raw_data ( l_node->data ), 0, unsigned int )
		= finc_access ( finc_data_get_raw_data ( l_node->data ), 0, unsigned int ) + 1;

	unref(p_node->data);
	p_node->data = finc_data_new_copy(l_node->data);
	unref ( l_node );
}

void finc_sys_inc ( FinCNode* p_node )
{
	FinCNode * l_node;

	l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );

	unref(p_node->data);
	p_node->data = finc_data_new_copy(l_node->data);

	finc_access ( finc_data_get_raw_data ( l_node->data ), 0, unsigned int )
		= finc_access ( finc_data_get_raw_data ( l_node->data ), 0, unsigned int ) + 1;
	unref ( l_node );
}

void finc_sys_predec ( FinCNode* p_node )
{
	FinCNode * l_node;

	l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );

	finc_access ( finc_data_get_raw_data ( l_node->data ), 0, unsigned int )
		= finc_access ( finc_data_get_raw_data ( l_node->data ), 0, unsigned int ) - 1;

	unref(p_node->data);
	p_node->data = finc_data_new_copy(l_node->data);
	unref ( l_node );
}

void finc_sys_dec ( FinCNode* p_node )
{
	FinCNode * l_node;

	l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );
	p_node->data = finc_data_new_copy(l_node->data);

	finc_access ( finc_data_get_raw_data ( l_node->data ), 0, unsigned int )
		= finc_access ( finc_data_get_raw_data ( l_node->data ), 0, unsigned int ) - 1;
	unref ( l_node );
}

void finc_sys_cmp_l ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	if ( finc_access ( finc_data_get_raw_data ( l_data_left ), 0, unsigned int )
	    < finc_access ( finc_data_get_raw_data ( l_data_right ), 0, unsigned int ) )
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = TRUE;
	else
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = FALSE;

	unref (l_left);
	unref (l_right);
	unref (l_data_left);
	unref (l_data_right);

	unref (p_node->data);
	p_node->data = l_data;
}

void finc_sys_cmp_g ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	if ( finc_access ( finc_data_get_raw_data ( l_data_left ), 0, unsigned int )
	    > finc_access ( finc_data_get_raw_data ( l_data_right ), 0, unsigned int ) )
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = TRUE;
	else
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = FALSE;

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_cmp_le ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	if ( finc_access ( finc_data_get_raw_data ( l_data_left ), 0, unsigned int )
	        <= finc_access ( finc_data_get_raw_data ( l_data_right ), 0, unsigned int ) )
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = TRUE;
	else
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = FALSE;

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_cmp_ge ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	if ( finc_access ( finc_data_get_raw_data ( l_data_left ), 0, unsigned int )
	        >= finc_access ( finc_data_get_raw_data ( l_data_right ), 0, unsigned int ) )
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = TRUE;
	else
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = FALSE;

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_cmp_ne ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	if ( finc_access ( finc_data_get_raw_data ( l_data_left ), 0, unsigned int )
	    != finc_access ( finc_data_get_raw_data ( l_data_right ), 0, unsigned int ) )
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = TRUE;
	else
	    finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = FALSE;

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_cmp_e ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	if ( finc_access ( finc_data_get_raw_data ( l_data_left ), 0, unsigned int )
	        == finc_access ( finc_data_get_raw_data ( l_data_right ), 0, unsigned int ) )
		finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = TRUE;
	else
		finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool ) = FALSE;

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_block ( FinCNode* p_node )
{
	FinCNode * l_node;
	unsigned int l_size;
	unsigned int i;

	l_size = vector_get_size ( p_node->vector_node );

	for ( i = 0; i < l_size; i++ )
	{
		l_node = (FinCNode*)vector_at ( p_node->vector_node, i );
		finc_node_evaluate ( l_node );
		unref ( l_node );
	}
}

void finc_sys_comma( FinCNode* p_node)
{
	FinCNode* l_node1;
	FinCNode* l_node2;
	FinCType* l_type;
	FinCData* l_data;

	l_node1 = (FinCNode*)vector_at (p_node->vector_node, 0);
	l_node2 = (FinCNode*)vector_at (p_node->vector_node, 1);

	finc_node_evaluate (l_node1);
	finc_node_evaluate (l_node2);

	l_type = finc_type_new (l_node2->data->type->type, FinCArrayType_None, 0);
	l_data = finc_data_new (l_type, NULL);
	unref(l_type);
	unref(l_node1);

	unref(p_node->data);
	finc_data_assign(l_data, l_node2->data);
	unref(l_node2);

	p_node->data = l_data;
}

void finc_sys_condition( FinCNode* p_node )
{
	FinCNode* l_node1;
	FinCNode* l_node2;
	FinCNode* l_node3;
	FinCType* l_type;
	FinCData* l_data;

	l_node1 = (FinCNode*)vector_at (p_node->vector_node, 0);
	l_node2 = (FinCNode*)vector_at (p_node->vector_node, 1);
	l_node3 = (FinCNode*)vector_at (p_node->vector_node, 2);

	finc_node_evaluate (l_node1);
	if ( finc_access ( finc_data_get_raw_data ( l_node1->data ), 0, Bool ) )
	{
		finc_node_evaluate ( l_node2 );
		l_type = finc_type_new(l_node2->data->type->type, FinCArrayType_None, 0);
		l_data = finc_data_new(l_type, NULL);
		unref(l_type);

		finc_data_assign(l_data, l_node2->data);
		p_node->data = l_data;
	}
	else
	{
		finc_node_evaluate ( l_node3 );
		l_type = finc_type_new(l_node3->data->type->type, FinCArrayType_None, 0);
		l_data = finc_data_new(l_type, NULL);
		unref(l_type);

		finc_data_assign(l_data, l_node3->data);
		p_node->data = l_data;
	}

	unref(l_node1);
	unref(l_node2);
	unref(l_node3);
}

void finc_sys_logic_or ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
		finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) ||
		finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_logic_and ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );
	unref ( l_type );

	finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
		finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) &&
		finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_not ( FinCNode* p_node )
{
	FinCNode * l_node;
	FinCType* l_type;
	FinCData* l_data;

	l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );

	l_type = finc_type_new ( FinCType_Bool, FinCArrayType_None, 0 );
	l_data = finc_data_new ( l_type, NULL );

	finc_access ( finc_data_get_raw_data ( l_data ), 0, Bool )
		= ! finc_access ( finc_data_get_raw_data ( l_node->data ), 0, Bool );

	unref ( l_node );
	unref(p_node->data);
	p_node->data = l_data;
}

void finc_sys_or ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) |
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) |
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) |
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		/* do not support or operator */
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) |
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support OR operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_and ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) &
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) &
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) &
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		/* do not support and operator */
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) &
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support AND operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_xor ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) ^
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) ^
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) ^
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		/* do not support xor operator */
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) ^
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support XOR operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_bitwise ( FinCNode* p_node )
{
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_right;

	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_right->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			~ finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			~ finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			~ finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		/* do not support bitwise operator */
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			~ finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support BIT NEGATIVE operation.\n");
		break;
	}

	unref ( l_right );
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_shl ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) <<
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) <<
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) <<
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		/* do not support shl operator */
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) <<
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support SHIFT LEFT operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_shr ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) >>
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) >>
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) >>
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		/* do not support shr operator */
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) >>
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support SHIFT RIGHT operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_add ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) +
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) +
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) +
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		l_type = finc_type_new ( FinCType_Double, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, double ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, double ) +
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, double );
		break;
	#endif
	#ifdef USING_FLOAT
	case FinCType_Float:
		l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, float ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, float) +
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, float );
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) +
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support ADD operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_sub ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) -
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) -
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) -
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		l_type = finc_type_new ( FinCType_Double, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, double ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, double ) -
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, double );
		break;
	#endif
	#ifdef USING_FLOAT
	case FinCType_Float:
		l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, float ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, float) -
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, float );
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) -
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support SUB operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_mul ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) *
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) *
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) *
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		l_type = finc_type_new ( FinCType_Double, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, double ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, double ) *
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, double );
		break;
	#endif
	#ifdef USING_FLOAT
	case FinCType_Float:
		l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, float ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, float) *
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, float );
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) *
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support MUL operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_div ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) /
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) /
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) /
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		l_type = finc_type_new ( FinCType_Double, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, double ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, double ) /
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, double );
		break;
	#endif
	#ifdef USING_FLOAT
	case FinCType_Float:
		l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, float ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, float) /
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, float );
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) /
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support DIV operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_mod ( FinCNode* p_node )
{
	FinCNode * l_left;
	FinCNode* l_right;
	FinCType* l_type;
	FinCData* l_data = NULL;
	FinCData* l_data_left;
	FinCData* l_data_right;

	l_left = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	l_right = (FinCNode*)vector_at ( p_node->vector_node, 1 );

	finc_node_evaluate ( l_left );
	l_data_left = finc_node_take_data (l_left);
	finc_node_evaluate ( l_right );
	l_data_right = finc_node_take_data (l_right);

	switch ( l_data_left->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, int ) %
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, char ) %
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, short ) %
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		/* do not support double mod operator */
		break;
	#endif
	#ifdef USING_FLOAT
	case FinCType_Float:
		/* do not support float mod operator */
		break;
		
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			finc_access ( finc_data_get_raw_data ( l_data_left ), 0, long ) %
			finc_access ( finc_data_get_raw_data ( l_data_right ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support MOD operation.\n");
		break;
	}

	unref ( l_left );
	unref ( l_right );
	unref (l_data_left);
	unref (l_data_right);

	unref ( p_node->data );
	p_node->data = l_data;
}

void finc_sys_negative( FinCNode* p_node )
{
	FinCNode* l_node;
	FinCType* l_type;
	FinCData* l_data = NULL;

	l_node = (FinCNode*)vector_at ( p_node->vector_node, 0 );
	finc_node_evaluate ( l_node );

	switch ( l_node->data->type->type )
	{
	case FinCType_Int:
		l_type = finc_type_new ( FinCType_Int, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, int ) = 
			- finc_access ( finc_data_get_raw_data ( l_node->data ), 0, int );
		break;

	case FinCType_Char:
		l_type = finc_type_new ( FinCType_Char, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, char ) =
			- finc_access ( finc_data_get_raw_data ( l_node->data ), 0, char );
		break;

	case FinCType_Short:
		l_type = finc_type_new ( FinCType_Short, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, short ) =
			- finc_access ( finc_data_get_raw_data ( l_node->data ), 0, short );
		break;
	#ifdef USING_DOUBLE
	case FinCType_Double:
		l_type = finc_type_new ( FinCType_Double, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, double ) =
			- finc_access ( finc_data_get_raw_data ( l_node->data ), 0, double );
		break;
	#endif
	#ifdef USING_FLOAT
	case FinCType_Float:
		l_type = finc_type_new ( FinCType_Float, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, float ) =
			- finc_access ( finc_data_get_raw_data ( l_node->data ), 0, float );
		break;
	#endif
	#ifdef USING_LONG
	case FinCType_Long:
		l_type = finc_type_new ( FinCType_Long, FinCArrayType_None, 0 );
		l_data = finc_data_new ( l_type, NULL );
		unref ( l_type );

		finc_access ( finc_data_get_raw_data ( l_data ), 0, long ) =
			- finc_access ( finc_data_get_raw_data ( l_node->data ), 0, long );
		break;
	#endif
	default:
		printf("this data type not support MOD operation.\n");
		break;
	}

	unref ( l_node );
	unref(p_node->data);
	p_node->data = l_data;
}
