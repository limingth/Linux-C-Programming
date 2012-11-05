#ifndef _FinC_FIELD_H_
#define _FinC_FIELD_H_

#include <tiny/global.h>
#include <tiny/object.h>
#include <tiny/string.h>

#include <finc/fincconfig.h>
#include <finc/finctype.h>

#define FinC_FIELD(obj) ((FinCField*) obj)

struct _FinCField
{
	Object parent;

	String* name;
	FinCType* type;

	int offset;
	int index;
};

FinCField* finc_field_new (String* p_name, FinCType* p_type);
void finc_field_destroy (Object* self);

#define finc_field_set_offset( field, os)	(field)? (field)->offset = (os) : 0
#define finc_field_get_offset( field )		(field)? (field)->offset : 0

#define finc_field_set_index(field, i)		(field)->index = i
#define finc_field_get_index(field)		(field)? (field)->index : 0

#endif
