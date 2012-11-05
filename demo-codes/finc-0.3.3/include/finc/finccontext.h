#ifndef _FINC_CONTEXT_H_
#define _FINC_CONTEXT_H_

#include <tiny/global.h>
#include <tiny/object.h>
#include <tiny/string.h>
#include <tiny/list.h>
#include <tiny/hash.h>

#include <finc/fincconfig.h>
#include <finc/fincdebug.h>
#include <finc/fincfunc.h>
#include <finc/fincvar.h>
#include <finc/fincstruct.h>

typedef struct _FinCContext FinCContext;
struct _FinCContext
{
	Object parent;

	Bool script_return;
	Bool script_continue;
	Bool script_break;
	Bool script_in_cycle;

	HashTable* hash_global;
	HashTable* hash_local;
	HashTable* hash_functions;
	HashTable* hash_struct;
	
	int error;
};

extern FinCContext* g_finc_context;

FinCContext* finc_context_new ();
void finc_context_destroy (Object* self);

#define finc_context_error_inc( context ) (context)->error ++
#define finc_context_error_clear( context ) (context)->error = 0

FinCFunc* finc_context_add_func_sys (FinCContext* self, unsigned char* p_name, FinCFuncSys p_sys);
FinCFunc* finc_context_add_func_sys_api (FinCContext* self, unsigned char* p_name, void* p_func);
FinCFunc* finc_context_add_func_native (FinCContext* self, unsigned char* p_name, void* p_native);
FinCFunc* finc_context_add_func_node (FinCContext* self, unsigned char* p_name, FinCNode* p_node);
#define finc_context_get_func( context, func_name) \
        hash_table_find( (context)->hash_functions, (ADT)(func_name))

void finc_context_add_var (FinCContext* self, FinCVar* p_var, Bool p_global);
FinCVar* finc_context_get_var (FinCContext* self, String* p_name);

#define finc_context_add_struct( context, struct_name ) \
        hash_table_insert( (context)->hash_struct, (ADT)(struct_name)->name, OBJECT(struct_name))
#define finc_context_get_struct( context, name ) \
	hash_table_find( (context)->hash_struct, (ADT)(name))

HashTable* finc_context_func_enter (FinCContext* self);
void finc_context_func_leave (FinCContext* self, HashTable* p_hash);

#endif
