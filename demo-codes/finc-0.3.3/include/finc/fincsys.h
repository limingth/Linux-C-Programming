#ifndef _FinC_SYS_H_
#define _FinC_SYS_H_

#include <tiny/global.h>
#include <tiny/string.h>
#include <tiny/vector.h>

#include <finc/fincconfig.h>
#include <finc/fincnode.h>
#include <finc/finclang.h>

typedef struct _FinCSys FinCSys;
struct _FinCSys
{
	Object parent;

	FinCLangEnv* env;
};

FinCSys* finc_sys_new();
void finc_sys_destroy(Object* self);
void finc_sys_init (FinCSys* self);

#endif
