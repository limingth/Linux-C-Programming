#include <tiny/library.h>

#ifdef HAVE_LIBRARY
static Library* library_new(unsigned char* libname);
static void library_destroy(Object* self);

static Bool library_equal_libname(ADT a, ADT b);

static Library* library_new(unsigned char* libname)
{
	Library* self;

	self = (Library*)mem_new(sizeof(Library));
	self->libname = string_new_str(libname);
	self->filename = string_new_str(libname);
	self->handler = (ADT)dlopen(libname, RTLD_LAZY | RTLD_GLOBAL);

	if (!self->handler)
	{
		fprintf(stderr, "%s\n", dlerror());
		unref(self);
		return NULL;
	}

	object_init_object((Object*)self, library_destroy);

	return self;
}

static void library_destroy(Object* self)
{
	if (!self)return;
		dlclose(((Library*)self)->handler);

	unref( ((Library*)self)->filename);
	unref( ((Library*)self)->libname);

	mem_destroy(self);
}

ADT library_symbol(Library* self, char* func)
{
	ADT handler;

	if (!self)return NULL;

	handler =  (ADT)dlsym(self->handler, func);

	if (!handler)
	{
		fprintf(stderr, "Unknown symbol: %s\n", func);
	}

	return handler;
}

static Bool library_equal_libname(ADT a, ADT b)
{
	Library* self;
	unsigned char* name;

	self = (Library*)a;
	name = (unsigned char*)b;

	return strcmp(string_get_str(self->libname), name)==0? TRUE:FALSE;
}

LibFactory* lib_factory_new()
{
	LibFactory* self;

	self = (LibFactory*)mem_new(sizeof(LibFactory));
	self->librarys = list_new();

	object_init_object((Object*)self, lib_factory_destroy);

	return self;
}

void lib_factory_destroy(Object* self)
{
	unref( ((LibFactory*)self)->librarys );

	mem_destroy(self);
}

Library* lib_factory_load_lib(LibFactory* self, unsigned char* libname)
{
	Library* lib;

	if (!self) return NULL;

	lib = (Library*) list_find(self->librarys, library_equal_libname, (ADT)libname);

	if ( !lib )
	{
		lib = library_new(libname);
		list_append(self->librarys, (ADT)lib);
	}

	return lib;
}

void lib_factory_unload_lib(LibFactory* self, Library* lib)
{
	Library* stand;

	if (!lib)
	{
		fprintf(stderr, "Error on unload a never loaded library.\n");
		return;
	}

	stand = list_find(self->librarys, NULL, (ADT)lib);
	if (stand)
	{
		if (stand->parent.refcount == 3)
		{
			list_remove_current(self->librarys);
			
			unref(stand);
			unref(lib);
		}
		else
		{
			unref(stand);
			unref(lib);
		}
	}
}

void lib_factory_unload_lib_name(LibFactory* self, unsigned char* libname)
{
	Library* stand;

	if (!self)
	{
		fprintf(stderr, "Source class unavailable.\n");
		return;
	}

	stand = list_find(self->librarys, library_equal_libname, (ADT)libname);
	if (stand)
	{
		if (stand->parent.refcount == 2)
		{
			list_remove_current(self->librarys);
			
			unref(stand);
		}
		else
		{
			unref(stand);
		}
	}
}

ADT lib_factory_create_object(LibFactory* self, unsigned char* libname)
{
	return NULL;
}

#endif
