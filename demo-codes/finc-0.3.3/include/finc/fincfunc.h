#ifndef _FinC_FUNC_H_
#define _FinC_FUNC_H_

#include <tiny/global.h>
#include <tiny/object.h>
#include <tiny/string.h>
#include <tiny/list.h>

#include <finc/fincconfig.h>
#include <finc/finctype.h>
#include <finc/fincnode.h>
#include <finc/fincfield.h>

typedef enum {
	FinCFuncType_None,
	FinCFuncType_Sys,
	FinCFuncType_Sys_Api,
	FinCFuncType_Native,
#if 0
	FinCFuncType_Native_Builtin,
#endif
	FinCFuncType_Node
} FinCFuncType;

typedef void (*FinCFuncSys)(FinCNode* p_node);
struct _FinCFunc
{
	Object parent;
	FinCFuncType type;

	String* name;
	FinCType* ret_type;

	FinCNode* node;
	FinCFuncSys sys;
	ADT native;

	Bool opt_param;

	Vector* vector_params;
};

#if 0
typedef struct _FinCNativeFunc FinCNativeFunc;
struct _FinCNativeFunc
{
	Object parent;
	FinCFuncType type;

	char *name;
	ADT native;
};
extern FinCNativeFunc g_finc_native_func[];

/*
Example for FinCNativeFunc definition
g_finc_native_func[] = 
{
{{1, NULL}, FinCFuncType_Native_Builtin, function1},
{{1, NULL}, FinCFuncType_Native_Builtin, function2},
{{1, NULL}, FinCFuncType_Native_Builtin, function3},
{{1, NULL}, FinCFuncType_Native_Builtin, function4},
NULL
};
*/
#endif

extern FinCData* g_finc_func_return;

FinCFunc* finc_func_new ();
void finc_func_destroy (Object* self);

void finc_func_set_sys (FinCFunc* self, String* p_name, FinCFuncSys p_sys);
void finc_func_set_sys_api (FinCFunc* self, String* p_name, ADT sys_api);
void finc_func_set_native (FinCFunc* self, String* p_name, void* p_native);
void finc_func_set_node (FinCFunc* self, String* p_name, FinCNode* p_node);

void finc_func_add_param (FinCFunc* self, FinCField* p_param);

FinCData* finc_func_call (FinCFunc* self, FinCNode* p_node);
FinCData* finc_func_native_call (FinCFunc* self, FinCNode* node);
FinCData* finc_func_native_call_f (FinCFunc* self, FinCNode* node);

#endif
