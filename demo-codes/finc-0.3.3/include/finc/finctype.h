#ifndef _FinC_TYPE_H_
#define _FinC_TYPE_H_

#include <tiny/global.h>
#include <tiny/object.h>
#include <tiny/string.h>

#include <finc/fincconfig.h>

#define FinC_TYPE(obj) ((FinCType*) obj)

typedef enum {
	FinCType_CONST = 1 << 0,
	FinCType_STATIC = 1 << 2,
	FinCType_Signed = 1 << 3,
	FinCType_Unsigned = 1 << 4,
	FinCType_Volatile = 1 << 5,
	FinCType_Register = 1 << 6,
	FinCType_Auto = 1 << 7,

	FinCType_Void = 1 << 8,
	FinCType_Char = 1 << 9,
	FinCType_Short = 1 << 10,
	FinCType_Int = 1 << 11,
	FinCType_Float = 1 << 12,
	FinCType_Double = 1 << 13,
	FinCType_Long = 1 << 14,
	FinCType_Bool = 1 << 15,

	FinCType_Pointer = 1 << 16,
	FinCType_String = 1 << 17,
	FinCType_Struct = 1 << 18,
	FinCType_Func = 1 << 19
} FinCTypeType;

typedef enum {
	FinCArrayType_None,
	FinCArrayType_Fixed,
	FinCArrayType_Dynamic
} FinCArrayType;

typedef struct _FinCData FinCData;
typedef struct _FinCField FinCField;
typedef struct _FinCType FinCType;
struct _FinCType
{
	Object parent;

	String* name;
	FinCTypeType type;

	FinCArrayType array_type;
	unsigned int  array_size;
};

FinCType* finc_type_new (FinCTypeType p_type, FinCArrayType p_array_type, unsigned int p_array_size);
FinCType* finc_type_new_name (unsigned char* p_name, FinCArrayType p_array_type, unsigned int p_array_size);
FinCType* finc_type_new_copy(FinCType* other);

void finc_type_destroy (Object* self);

unsigned int finc_type_get_size (FinCType* self);

#endif

