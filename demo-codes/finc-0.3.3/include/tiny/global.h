#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

#define addref(type, obj) (type*) object_addref (OBJECT (obj))
#define unref(obj) object_unref ((Object*) obj)

typedef void* ADT;
typedef short Bool;

typedef Bool (*EqualFunc) (ADT a, ADT b);
typedef void (*UserFunc) (ADT value, ADT data);

#include "mem.h"
#include "object.h"

#endif
