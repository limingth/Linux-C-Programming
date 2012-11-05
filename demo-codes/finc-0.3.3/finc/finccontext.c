#include <finc/finccontext.h>
#include <finc/finclang.h>
#include <finc/fincsys.h>
/*
#include <malloc.h>
*/
FinCContext* g_finc_context = NULL;

FinCContext* finc_context_new ()
{
    FinCContext *self;
    
    self = (FinCContext*)mem_new(sizeof(FinCContext));
    object_init_object (OBJECT (self), finc_context_destroy);
    
    self->hash_global = hash_table_new (string_hash, string_equal);
    self->hash_local = NULL;
    self->hash_functions = hash_table_new (string_hash, string_equal);
    
    self->script_return = FALSE;
    self->script_continue = FALSE;
    self->script_break = FALSE;
    self->script_in_cycle = FALSE;
    
    self->hash_struct = hash_table_new (string_hash, string_equal);
    
    self->error = 0;
    
    return self;
}

void finc_context_destroy (Object* self)
{
    unref ( ((FinCContext*)self)->hash_global);
    unref ( ((FinCContext*)self)->hash_local);
    unref ( ((FinCContext*)self)->hash_functions);
    unref ( ((FinCContext*)self)->hash_struct);
    mem_destroy (self);
}

FinCFunc* finc_context_add_func_sys (FinCContext* self, unsigned char* p_name, FinCFuncSys p_sys)
{
    FinCFunc* l_func;
    String*	l_name;
    
    l_func = finc_func_new ();
    l_name = string_new ();
    
    string_set_str (l_name, p_name);
    finc_func_set_sys (l_func, l_name, p_sys);
    
    hash_table_insert(self->hash_functions, (void*)l_func->name, OBJECT(l_func));
    
    unref (l_func);
    unref (l_name);
    
    return l_func;
}

FinCFunc* finc_context_add_func_sys_api (FinCContext* self, unsigned char* p_name, void* p_func)
{
    FinCFunc* l_func;
    String*	l_name;
    
    l_func = finc_func_new ();
    l_name = string_new ();
    
    string_set_str (l_name, p_name);
    finc_func_set_sys_api (l_func, l_name, p_func);
    
    hash_table_insert(self->hash_functions, (void*)l_func->name, (Object*)l_func);
    
    unref (l_func);
    unref (l_name);
    
    return l_func;
}

FinCFunc* finc_context_add_func_native (FinCContext* self, unsigned char* p_name, void* p_native)
{
    FinCFunc* l_func;
    String*	l_name;
    
    l_func = finc_func_new ();
    l_name = string_new ();
    
    string_set_str (l_name, p_name);
    finc_func_set_native (l_func, l_name, p_native);
    
    hash_table_insert(self->hash_functions, (void*)l_func->name, OBJECT(l_func));
    
    unref (l_func);
    unref (l_name);
    
    return l_func;
}

FinCFunc* finc_context_add_func_node (FinCContext* self, unsigned char* p_name, FinCNode* p_node)
{
    FinCFunc* l_func;
    String*	l_name;
    
    l_func = finc_func_new ();
    l_name = string_new ();
    
    string_set_str (l_name, p_name);
    finc_func_set_node (l_func, l_name, p_node);
    
    hash_table_insert(self->hash_functions, (void*)l_func->name, OBJECT(l_func));
    
    unref (l_func);
    unref (l_name);
    
    return l_func;
}

void finc_context_add_var (FinCContext* self, FinCVar* p_var, Bool p_global)
{
    FinCVar* l_var = NULL;

    if ((self->hash_local) && !p_global)
    {
		l_var = hash_table_find(self->hash_local, (ADT)p_var->name);
		if (!l_var) hash_table_insert(self->hash_local, (void*)p_var->name, OBJECT(p_var));
		else
		{
			printf("Runtime Error: there already exist a name as '%s' variable.\n", string_get_str(p_var->name));
			finc_context_error_inc( g_finc_context );
			unref(l_var);
		}
    }
    else
    {
		l_var = hash_table_find(self->hash_global, (ADT)p_var->name);
		if (!l_var) hash_table_insert (self->hash_global, (void*)p_var->name, OBJECT (p_var));
		else
		{
			printf("Runtime Error: there already exist a name as '%s' variable.\n", string_get_str(p_var->name));
			finc_context_error_inc( g_finc_context );
			unref(l_var);
		}
    }
}

FinCVar* finc_context_get_var (FinCContext* self, String* p_name)
{
    FinCVar* l_var;
    
    if (self->hash_local)
    {
		l_var = hash_table_find(self->hash_local, p_name);
		if (l_var) return l_var;
    }
    
    return hash_table_find(self->hash_global, p_name);
}

HashTable* finc_context_func_enter (FinCContext* self)
{
    HashTable* l_list;
    
    l_list = self->hash_local;
    self->hash_local = hash_table_new(string_hash, string_equal);
    
    return l_list;
}

void finc_context_func_leave (FinCContext* self, HashTable* p_hash)
{
    unref (self->hash_local);
    self->hash_local = p_hash;
}
