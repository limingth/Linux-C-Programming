#ifndef _FinC_VAR_H_
#define _FinC_VAR_H_

#include <tiny/global.h>
#include <tiny/object.h>
#include <tiny/string.h>

#include <finc/fincconfig.h>
#include <finc/fincdata.h>

#define FinC_VAR(obj) ((FinCVar*) obj)

typedef struct _FinCVar FinCVar;
struct _FinCVar
{
	Object 		parent;		/* base class is Object */

	String* 	name;		/* name of variable */
	FinCData* 	data;		/* data of variable */
};

FinCVar* finc_var_new (String* p_name, FinCData* p_data);
FinCVar* finc_var_new_copy (String* p_name, FinCData* p_data);

void finc_var_destroy (Object* self);

#endif

