#include <finc/fincdebug.h>

#ifdef FINC_DEBUG
#include <finc/fincvar.h>
#include <finc/finccontext.h>
#include <finc/finclib.h>

static int nb_tab = 0;
void finc_debug_node (FinCNode* p_node)
{
	unsigned int i;
	unsigned int l_size;

	if (!p_node)return;

	if (p_node->node_type == FinCNodeType_Func)
	{
		for (i=0; i<nb_tab; i++)
			printf ("\t");

		printf ("Expr Debug Func: '%s'\n", string_get_str (p_node->identifier));
		nb_tab++;

		l_size = vector_get_size (p_node->vector_node);      
		for (i=0; i<l_size; i++)
			finc_debug_node (finc_node_get (p_node, i));

		nb_tab--;
	}

	if (p_node->node_type == FinCNodeType_Block)
	{
		for (i=0; i<nb_tab; i++)
			printf ("\t");

		printf ("BLOCK\n");
		nb_tab++;

		l_size = vector_get_size (p_node->vector_node);      
		for (i=0; i<l_size; i++)
			finc_debug_node (finc_node_get (p_node, i));

		nb_tab--;
	}
}

void finc_debug_data (char* msg, FinCData* p_data)
{
	if (!p_data)return;

	if ( p_data->type->type & FinCType_Void )
	{
		printf("%s", msg);
		printf("data is void!\n");
		return;
	}

	if ( p_data->type->type & FinCType_Char )
	{
		printf("%s", msg);
		printf("data is char:%c\n", finc_access(p_data->raw, 0, char));
		return;
	}
	
	if ( p_data->type->type & FinCType_Short )
	{
		printf("%s", msg);
		printf("data is short:%d\n", finc_access(p_data->raw, 0, short));
		return;
	}

	if ( p_data->type->type & FinCType_Int )
	{
		printf("%s", msg);
		printf("data is int:%d\n", finc_access(p_data->raw, 0, int));
		return;
	}
	#ifdef USING_FLOAT
	if ( p_data->type->type & FinCType_Float )
	{
		printf("%s", msg);
		printf("data is float:%f\n", finc_access(p_data->raw, 0, float));
		return;
	}
	#endif
	#ifdef USING_DOUBLE
	if ( p_data->type->type & FinCType_Double )
	{
		printf("%s", msg);
		printf("data is double:%f\n", finc_access(p_data->raw, 0, double));
		return;
	}
	#endif
	if ( p_data->type->type & FinCType_Bool )
	{
		printf("%s", msg);
		printf("data is bool:%s\n", finc_access(p_data->raw, 0, Bool)? "true":"false");
		return;
	}

	if ( p_data->type->type & FinCType_String )
	{
		printf("%s", msg);
		printf("data is string:%s\n", finc_access(p_data->raw, 0, char*));
		return;
	}

	if ( p_data->type->type & FinCType_Struct )
	{
		printf("%s", msg);
		printf("data is a struct\n");
		return;
	}
}

void finc_debug_var (char* p_var)
{
	String* l_str;
	FinCVar* l_var;

	l_str = string_new();
	string_set_str(l_str, p_var);
	l_var = finc_context_get_var(g_finc_context, l_str);
	unref(l_str);

	if ( l_var )finc_debug_data("variable:", l_var->data);
	else printf("DEBUG: variable not founded!\n");
}

#endif
