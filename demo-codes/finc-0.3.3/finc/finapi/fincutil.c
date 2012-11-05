#include <finc/finapi/fincutil.h>

#ifdef USING_UTIL
#include <finc/fincfunc.h>
#include <finc/fincstruct.h>
#include <finc/fincvar.h>

extern FinCContext* g_finc_context;

void finc_list_func();
void finc_list_struct();
void finc_list_global();

void finc_util_init(FinC* finc)
{
	finc_insert_func(finc, "list_func", finc_list_func, "void", NULL);
	finc_insert_func(finc, "list_struct", finc_list_struct, "void", NULL);
	finc_insert_func(finc, "list_global", finc_list_global, "void", NULL);
}

static void finc_func_print(ADT value, ADT data)
{
	FinCFunc* func;

	func = (FinCFunc*)value;
	if ( func->type != FinCFuncType_Sys )
	{
		printf("%s\n", string_get_str(func->name));
	}
}

void finc_list_func()
{
	hash_table_foreach(g_finc_context->hash_functions, finc_func_print, NULL);
}

static void finc_struct_print(ADT value, ADT data)
{
	FinCStruct* _struct;

	_struct = (FinCStruct*)value;
	printf("%s\n", string_get_str(_struct->name));
}

void finc_list_struct()
{
	hash_table_foreach(g_finc_context->hash_struct, finc_struct_print, NULL);
}

static void finc_global_print(ADT value, ADT data)
{
	FinCVar* var;

	var = (FinCVar*)value;
	printf("%s\n", string_get_str(var->name));
}

void finc_list_global()
{
	hash_table_foreach(g_finc_context->hash_global, finc_global_print, NULL);
}

#endif
