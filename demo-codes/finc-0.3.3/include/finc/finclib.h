#ifndef _FINCLIB_H_
#define _FINCLIB_H_

#include <stdio.h>
#include <stdarg.h>

#include <finc/fincconfig.h>

#include <finc/finctype.h>
#include <finc/finccontext.h>
#include <finc/finclang.h>
#include <finc/fincdata.h>
#include <finc/fincsys.h>
#include <finc/fincparser.h>
#include <finc/finccontext.h>

//#define finc_access(ptr, offset, type) *((type*) (((char*) ptr) + offset))
#define finc_access(ptr, offset, type) (*(type*)((unsigned char*)ptr + offset))

typedef struct _FinC FinC;
struct _FinC
{
	Object parent;

	FinCLangEnv* env;
	FinCSys* sys_func;

	FinCContext* context;
};

typedef struct _FinCMethodItem  FinCMethodItem;
typedef struct _FinCMethodItem* FinCMethodTable;
struct _FinCMethodItem
{
	const char* method_name;
	void* method_ptr;
};

typedef struct _FinCFieldItem  FinCFieldItem;
typedef struct _FinCFieldItem* FinCFieldTable;
struct _FinCFieldItem
{
	const char* field_name;
	void* field_ptr;
	char size;
};

FinC* finc_init();
void finc_exit(FinC* self);

void finc_insert_var(FinC* self, unsigned char* type, unsigned char* name, ADT data);
void finc_remove_var(FinC* self, unsigned char* name);
ADT  finc_get_var(FinC* self, unsigned char* name);

void finc_insert_func(FinC* self, unsigned char* p_name, void* p_func, unsigned char* p_rettype, ...);
void finc_insert_sys_api(FinC* self, unsigned char* p_name, void* p_func, unsigned char* p_rettype);
ADT finc_call_func(FinC* self, unsigned char* func);

void finc_proc_method_table(FinC* self, FinCMethodTable table, int size);

#ifdef USING_FILE
void finc_run_script(FinC* self, unsigned char* filename);
#endif

void finc_run_string(FinC* self, unsigned char* str);

#endif
