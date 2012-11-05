#ifndef _FinC_String_H_
#define _FinC_String_H_

#include <tiny/object.h>
#include <tiny/string.h>
#include <tiny/vector.h>

#include <finc/fincconfig.h>
#include <finc/fincdata.h>
#include <finc/finclib.h>
#include <finc/finctype.h>

#ifdef USING_STRING_API
void finc_string_init(FinC* finc);

FinCData* finc_string_length(Vector* v);
FinCData* finc_string_compare(Vector* v);
FinCData* finc_string_equal(Vector* v);

FinCData* finc_string_copy(Vector* v);
FinCData* finc_string_add(Vector* v);
FinCData* finc_string_sub(Vector* v);

FinCData* finc_string_find(Vector* v);
FinCData* finc_string_find_ref(Vector* v);

FinCData* finc_string_replace(Vector* v);

FinCData* finc_string_begin_with(Vector* v);
FinCData* finc_string_end_with(Vector* v);

FinCData* finc_string_toupper(Vector* v);
FinCData* finc_string_tolower(Vector* v);

FinCData* finc_string_splite(Vector* v);
FinCData* finc_string_join(Vector* v);

FinCData* finc_string_set_size(Vector* v);

#endif

#endif
