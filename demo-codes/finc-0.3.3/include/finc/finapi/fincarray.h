#ifndef _FinC_ARRAY_H_
#define _FinC_ARRAY_H_

#include <finc/fincconfig.h>

#ifdef USING_ARRAY_API
#include <tiny/vector.h>
#include <tiny/object.h>

#include <finc/finclib.h>
#include <finc/fincdata.h>
#include <finc/finctype.h>

/*API for Array*/
void finc_array_init(FinC* finc);

FinCData* finc_array_insert(Vector* v);
FinCData* finc_array_remove(Vector* v);
FinCData* finc_array_append(Vector* v);
FinCData* finc_array_prepend(Vector* v);

FinCData* finc_array_size(Vector* v);

FinCData* finc_array_find(Vector* v);

FinCData* finc_array_first(Vector* v);
FinCData* finc_array_next(Vector* v);
FinCData* finc_array_prev(Vector* v);
FinCData* finc_array_last(Vector* v);
FinCData* finc_array_current(Vector* v);

FinCData* finc_array_pos(Vector* v);
#endif

#endif
