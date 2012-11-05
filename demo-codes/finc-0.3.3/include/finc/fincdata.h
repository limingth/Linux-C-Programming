#ifndef _FinC_DATA_H_
#define _FinC_DATA_H_

#include <tiny/global.h>
#include <tiny/string.h>
#include <tiny/vector.h>

#include <finc/fincconfig.h>
#include <finc/finctype.h>

#define FinC_DATA(obj) ((FinCData*) obj)

struct _FinCData
{
    Object 		parent;			/* base class is Object */

    FinCType* 	type;			/* type of data */
    Vector* 	vector_child;	/* member of children */
    FinCData* 	pointer;		/* pointer */
    
    Bool 		ref;
    int 		array_stand;	/* stand offset of current array */
   	ADT			raw;			/* abstract data type */
};

FinCData* finc_data_new (FinCType* p_type, ADT p_ref);
FinCData* finc_data_new_data ( FinCType* p_type, ADT p_ref );
FinCData* finc_data_new_copy (FinCData* p_data);
FinCData* finc_data_new_string (unsigned char* p_str);
FinCData* finc_data_new_raw_string (unsigned char* p_str);

void finc_data_destroy (Object* self);

void finc_data_init_data (ADT self, ADT data);

String* finc_data_get_string (FinCData* self);

void finc_data_set_string (FinCData* self, String* p_value);
void finc_data_assign (FinCData* self, FinCData* p_src);

FinCData* finc_data_get_index (FinCData* self, int p_index);

ADT finc_data_get_ptr (FinCData* self);

void finc_data_set_pointer (FinCData* self, FinCData* p_raw);
#define finc_data_get_pointer(data) addref(FinCData, (data)->pointer)
#define finc_data_get_raw_data(data) data? ((ADT)(data)->raw) : NULL
/*
get a Struct's field, and the field offset is p_offset.
*/
FinCData* finc_data_get_field (FinCData* self, int p_index);

#endif
