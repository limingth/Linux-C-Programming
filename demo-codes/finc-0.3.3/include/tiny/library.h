#ifndef _LIBRARY_H_
#define _LIBRARY_H_


#include <tiny/global.h>
#include <tiny/string.h>
#include <tiny/list.h>

#ifdef HAVE_LIBRARY

#include <dlfcn.h>
typedef struct _Library Library;
struct _Library
{
	Object parent;
	String* filename;
	String* libname;

	ADT handler;
};
ADT library_symbol(Library* self, char* func);

/*class LibFactory*/
typedef struct _LibFactory LibFactory;
struct _LibFactory
{
	Object parent;
	List* librarys;
};

LibFactory* lib_factory_new();
void lib_factory_destroy(Object* self);

Library* lib_factory_load_lib(LibFactory* self, unsigned char* libname);
void lib_factory_unload_lib(LibFactory* self, Library* lib);
void lib_factory_unload_lib_name(LibFactory* self, unsigned char* libname);

ADT lib_factory_create_object(LibFactory* self, unsigned char* libname);

#endif

#endif
