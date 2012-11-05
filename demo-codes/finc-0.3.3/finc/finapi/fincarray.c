#include <finc/finapi/fincarray.h>

#ifdef USING_STRING_API

void finc_array_init(FinC* finc)
{
	finc_insert_sys_api(finc, "array_insert", (ADT)finc_array_insert, "void");
	finc_insert_sys_api(finc, "array_remove", (ADT)finc_array_remove, "void");
	finc_insert_sys_api(finc, "array_append", (ADT)finc_array_append, "void");
	finc_insert_sys_api(finc, "array_prepend", (ADT)finc_array_prepend, "void");
	finc_insert_sys_api(finc, "array_size", (ADT)finc_array_size, "int");
	finc_insert_sys_api(finc, "array_find", (ADT)finc_array_find, "void");
	finc_insert_sys_api(finc, "array_first", (ADT)finc_array_first, "pointer");
	finc_insert_sys_api(finc, "array_next", (ADT)finc_array_next, "pointer");
	finc_insert_sys_api(finc, "array_prev", (ADT)finc_array_prev, "pointer");
	finc_insert_sys_api(finc, "array_last", (ADT)finc_array_last, "pointer");
	finc_insert_sys_api(finc, "array_current", (ADT)finc_array_current, "pointer");
	finc_insert_sys_api(finc, "array_pos", (ADT)finc_array_pos, "int");
}

/*
void array_insert(array a, ADT item, int index)
*/
FinCData* finc_array_insert(Vector* v)
{
	FinCData* array;
	FinCData* item;
	FinCData* data_index;
	int index;

	array = vector_at(v, 0);
	item = vector_at(v, 1);
	data_index = vector_at(v, 2);

	if (!array || !item || !data_index)
	{
		unref(array);
		unref(item);
		unref(data_index);
		return NULL;
	}

	index = finc_access(data_index->raw, 0, int);

	return NULL;
}

/*
void array_remove(array a, int index)
*/
FinCData* finc_array_remove(Vector* v)
{
	FinCData* array = NULL;
	FinCData* index = NULL;

	array = (FinCData*)vector_at(v, 0);
	index = (FinCData*)vector_at(v, 1);
	if ( (!array) || (array->type->array_type != FinCArrayType_Dynamic) || (!index))
	{
		unref(array);
		unref(index);
		return NULL;
	}

	return NULL;
}

/*
void array_append(array a, ADT item)
*/
FinCData* finc_array_append(Vector* v)
{
	FinCData* array = NULL;
	FinCData* item = NULL;

	array = (FinCData*)vector_at(v, 0);
	item  = (FinCData*)vector_at(v, 1);

	if ( (!array) || (array->type->array_type != FinCArrayType_Dynamic) || (!item))
	{
		unref(array);
		unref(item);
		return NULL;
	}

	return NULL;
}

/*
void array_prepend(array a, ADT item)
*/
FinCData* finc_array_prepend(Vector* v)
{
	FinCData* array = NULL;
	FinCData* item = NULL;

	array = (FinCData*)vector_at(v, 0);
	item = (FinCData*)vector_at(v, 1);

	if ( (!array) || (array->type->array_type != FinCArrayType_Dynamic) || (!item))
	{
		unref(array);
		unref(item);
		return NULL;
	}

	return NULL;
}

/*
int array_size(array a)
*/
FinCData* finc_array_size(Vector* v)
{
	FinCData* array;
	FinCData* result;
	FinCType* type;

	array = (FinCData*)vector_at(v, 0);

	if(!array) return NULL;

	type = finc_type_new(FinCType_Int, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);
	unref(type);

	finc_access(result->raw, 0, unsigned int) = array->type->array_size;
	unref(array);

	return result;
}

/*
ADT array_find(array a, function func, ADT item)
*/
FinCData* finc_array_find(Vector* v)
{
	return NULL;
}

/*
ADT array_first(array a)
*/
FinCData* finc_array_first(Vector* v)
{
	FinCData* array;
	FinCData* first;
	FinCData* result = NULL;

	array = (FinCData*)vector_at(v, 0);
	if (!array) return NULL;

	first = finc_data_get_index ( array, 0 );
	if(first)result = finc_data_new_copy(first);

	unref(first);
	unref(array);

	return result;
}

/*
ADT array_next(array a)
*/
FinCData* finc_array_next(Vector* v)
{
	FinCData* array;
	FinCData* next;
	FinCData* result = NULL;

	array = (FinCData*)vector_at(v, 0);
	if (!array) return NULL;

	array->array_stand = array->array_stand == array->type->array_size - 1 ?
		array->type->array_size-1 : array->array_stand+1;

	next = finc_data_get_index ( array, array->array_stand );
	if(next)result = finc_data_new_copy(next);

	unref(next);
	unref(array);

	return result;
}

/*
ADT array_prev(array a)
*/
FinCData* finc_array_prev(Vector* v)
{
	FinCData* array;
	FinCData* prev;
	FinCData* result = NULL;

	array = (FinCData*)vector_at(v, 0);
	if (!array) return NULL;

	array->array_stand = array->array_stand == 0? 0 : array->array_stand-1;

	prev = finc_data_get_index ( array, array->array_stand );
	if(prev)result = finc_data_new_copy(prev);

	unref(prev);
	unref(array);

	return result;
}

/*
ADT array_last(array a)
*/
FinCData* finc_array_last(Vector* v)
{
	FinCData* array;
	FinCData* last;
	FinCData* result = NULL;

	array = (FinCData*)vector_at(v, 0);
	if (!array) return NULL;

	last = finc_data_get_index ( array, array->type->array_size );
	if(last)result = finc_data_new_copy(last);

	unref(last);
	unref(array);

	return result;
}

/*
ADT array_current(array a)
*/
FinCData* finc_array_current(Vector* v)
{
	FinCData* array;
	FinCData* current;
	FinCData* result = NULL;

	array = (FinCData*)vector_at(v, 0);
	if (!array) return NULL;

	current = finc_data_get_index ( array, array->array_stand );
	if(current)result = finc_data_new_copy(current);

	unref(current);
	unref(array);

	return result;
}

/*
int array_pos(array a)
*/
FinCData* finc_array_pos(Vector* v)
{
	FinCData* array;
	FinCData* result;
	FinCType* type;

	array = (FinCData*)vector_at(v, 0);
	if (!array) return NULL;

	type = finc_type_new(FinCType_Int, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);

	finc_access(result->raw, 0, int) = array->array_stand;

	unref(type);
	unref(array);

	return result;
}

#endif
