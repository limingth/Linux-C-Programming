#include <finc/finapi/fincstring.h>

#ifdef USING_STRING_API

void finc_string_init(FinC* finc)
{
	finc_insert_sys_api(finc, "string_length", (ADT)finc_string_length, "int");
	finc_insert_sys_api(finc, "string_compare", (ADT)finc_string_compare, "int");
	finc_insert_sys_api(finc, "string_equal", (ADT)finc_string_equal, "bool");
	finc_insert_sys_api(finc, "string_add", (ADT)finc_string_add, "string");
	finc_insert_sys_api(finc, "string_copy", (ADT)finc_string_copy, "string");
	finc_insert_sys_api(finc, "string_sub", (ADT)finc_string_sub, "string");
	finc_insert_sys_api(finc, "string_find", (ADT)finc_string_find, "int");
	finc_insert_sys_api(finc, "string_find_ref", (ADT)finc_string_find_ref, "int");
	finc_insert_sys_api(finc, "string_replace", (ADT)finc_string_replace, "string");
	finc_insert_sys_api(finc, "string_begin_with", (ADT)finc_string_begin_with, "bool");
	finc_insert_sys_api(finc, "string_end_with", (ADT)finc_string_end_with, "bool");
	finc_insert_sys_api(finc, "string_toupper", (ADT)finc_string_toupper, "void");
	finc_insert_sys_api(finc, "string_tolower", (ADT)finc_string_tolower, "void");
	finc_insert_sys_api(finc, "string_splite", (ADT)finc_string_splite, "string");
	finc_insert_sys_api(finc, "string_join", (ADT)finc_string_join, "string");
	finc_insert_sys_api(finc, "string_set_size", (ADT)finc_string_set_size, "void");
}

/*
int string_length(string src)
*/
FinCData* finc_string_length(Vector* v)
{
	FinCData* str;
	FinCData* result;
	FinCType* type;

	str = (FinCData*)vector_at(v, 0);

	if (!str)return NULL;

	type = finc_type_new(FinCType_Int, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);
	unref(type);
	finc_access(result->raw, 0, unsigned int) = strlen(finc_access(str->raw, 0, unsigned char*));
	unref(str);

	return result;
}

/*
int string_compare(string str1, string str2)
*/
FinCData* finc_string_compare(Vector* v)
{
	FinCData* src1, *src2;
	FinCData* result;
	FinCType* type;
	unsigned char *sp1, *sp2;

	src1 = (FinCData*)vector_at(v, 0);
	if (!src1)return NULL;
	sp1 = finc_access(src1->raw, 0, unsigned char*);

	src2 = (FinCData*)vector_at(v, 1);
	if (!src2)
	{
		unref(src1);
		return NULL;
	}
	sp2 = finc_access(src2->raw, 0, unsigned char*);

	type = finc_type_new(FinCType_Int, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);
	unref(type);
	finc_access(result->raw, 0, unsigned int) = strcmp(sp1, sp2);

	unref(src1);
	unref(src2);

	return result;
}

/*
bool string_equal(string str1, string str2)
*/
FinCData* finc_string_equal(Vector* v)
{
	FinCData* src1, *src2;
	FinCData* result;
	FinCType* type;
	unsigned char *sp1, *sp2;

	src1 = (FinCData*)vector_at(v, 0);
	if (!src1)return NULL;
	sp1 = finc_access(src1->raw, 0, unsigned char*);

	src2 = (FinCData*)vector_at(v, 1);
	if (!src2)
	{
		unref(src1);
		return NULL;
	}
	sp2 = finc_access(src2->raw, 0, unsigned char*);

	type = finc_type_new(FinCType_Bool, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);
	unref(type);
	finc_access(result->raw, 0, unsigned int) = strcmp(sp1, sp2)==0? TRUE:FALSE;

	unref(src1);
	unref(src2);

	return result;
}

/*
string string_copy(string str)
*/
FinCData* finc_string_copy(Vector* v)
{
	FinCData* src;
	FinCData* result;

	src = (FinCData*)vector_at(v, 0);
	if (!src)return NULL;

	result = finc_data_new_copy(src);

	unref(src);
	return result;
}

/*
string string_add(string str1, string str2, string str3, ...)
*/
FinCData* finc_string_add(Vector* v)
{
	FinCData* src;
	FinCData* result;
	char* org;
	int i;

	org = NULL;
	for ( i=0; i<vector_get_size(v); i++)
	{
		src = (FinCData*)vector_at(v, i);
		if (!org)
		{
			org = (char*)mem_new(strlen(finc_access(src->raw, 0, unsigned char*))+1);
			strcpy(org, finc_access(src->raw, 0, unsigned char*));
		}
		else
		{
			org = (char*)mem_resize(org, strlen(org)+strlen(finc_access(src->raw, 0, unsigned char*))+1);
			strcat(org, finc_access(src->raw, 0, unsigned char*));
		}
		unref(src);
	}

	result = finc_data_new_string(org);
	mem_destroy(org);
	return result;
}

FinCData* finc_string_sub(Vector* v)
{
	FinCData* src;
	FinCData* begin, *end;
	int i_begin, i_end;
	FinCData* result;
	char *org, *p, *q, *temp;

	src = vector_at(v, 0);
	if (!src)return NULL;
	p = finc_access(src->raw, 0, unsigned char*);

	begin = vector_at(v, 1);
	if (!begin)
	{
		unref(src);
		return NULL;
	}
	i_begin = finc_access(begin->raw, 0, int);

	end = vector_at(v, 2);
	if (!end) i_end = strlen(p);
	else i_end = finc_access(end->raw, 0, int);
	if (i_begin>i_end)
	{
		unref(src);
		unref(begin);
		return NULL;
	}

	org = (char*)mem_new((i_end-i_begin+1)*sizeof(char));
	q = org;
	temp = p;
	p = p + i_begin;
	while ( p < temp+i_end )*q++ = *p++;
	*q = '\0';

	result = finc_data_new_string(org);
	mem_destroy(org);

	unref(src);
	unref(begin);
	unref(end);
	return result;
}

/*
int string_find(string str, string str1)
int string_find(string str, char ch)
*/
FinCData* finc_string_find(Vector* v)
{
	FinCData* str;
	FinCData* dest;
	FinCData* result;
	FinCType* type;
	int l_result;
	char ch;
	unsigned char *p, *q;

	str = vector_at(v, 0);
	if (!str)return NULL;
	p = finc_access(str->raw, 0, unsigned char*);

	dest = vector_at(v, 1);
	if (!dest)
	{
		unref(str);
		return NULL;
	}

	type = finc_type_new(FinCType_Int, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);
	unref(type);

	l_result = 0;
	if (dest->type->type & FinCType_String)
	{
		q = finc_access(dest->raw, 0, unsigned char*);
		while (*p)
		{
			if (strncmp(p, q, strlen(q))==0)break;
			l_result++;
			p++;
		}

		if (!*p)l_result = -1;
	}
	else if ( dest->type->type & FinCType_Char )
	{
		ch = finc_access(dest->raw, 0, char);
		while (*p)
		{
			if (*p++==ch)break;
			l_result++;
		}

		if (!*p)l_result = -1;
	}

	finc_access(result->raw, 0, int) = l_result;
	unref(str);
	unref(dest);

	return result;
}

/*
int string_find_ref(string str, string str1)
int string_find_ref(string str, char ch)
*/
FinCData* finc_string_find_ref(Vector* v)
{
	FinCData* str;
	FinCData* dest;
	FinCData* result;
	FinCType* type;
	int l_result;
	char ch;
	unsigned char *p, *q;

	str = vector_at(v, 0);
	if (!str)return NULL;
	p = finc_access(str->raw, 0, unsigned char*);
	l_result = strlen(p);
	p = p + l_result;

	dest = vector_at(v, 1);
	if (!dest)
	{
		unref(str);
		return NULL;
	}

	type = finc_type_new(FinCType_Int, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);
	unref(type);

	if (dest->type->type & FinCType_String)
	{
		q = finc_access(dest->raw, 0, unsigned char*);
		while (p!=finc_access(str->raw, 0, unsigned char*))
		{
			if (strncmp(p, q, strlen(q))==0)break;
			l_result--;
			p--;
		}
	}
	else if ( dest->type->type & FinCType_Char )
	{
		ch = finc_access(dest->raw, 0, char);
		while (p!=finc_access(str->raw, 0, unsigned char*))
		{
			if (*p--==ch)break;
			l_result--;
		}
	}

	finc_access(result->raw, 0, int) = l_result;
	unref(str);
	unref(dest);

	return result;
}

/*
int string_replace(string str, string src, string dest)
*/
FinCData* finc_string_replace(Vector* v)
{
	return NULL;
}

/*
bool string_begin_with(string str, string str1)
bool string_begin_with(string str, char ch)
*/
FinCData* finc_string_begin_with(Vector* v)
{
	FinCData* str;
	FinCData* dest;
	FinCData* result;
	FinCType* type;
	int l_result;
	char ch;
	unsigned char *p, *q;

	str = vector_at(v, 0);
	if (!str)return NULL;
	p = finc_access(str->raw, 0, unsigned char*);

	dest = vector_at(v, 1);
	if (!dest)
	{
		unref(str);
		return NULL;
	}

	type = finc_type_new(FinCType_Bool, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);
	unref(type);

	l_result = 0;
	if (dest->type->type & FinCType_String)
	{
		q = finc_access(dest->raw, 0, unsigned char*);
		if (strncmp(p, q, strlen(q))==0)l_result=1;
	}
	else if ( dest->type->type & FinCType_Char )
	{
		ch = finc_access(dest->raw, 0, char);
		if (*p==ch) l_result=1;
	}

	finc_access(result->raw, 0, Bool) = l_result==1? TRUE:FALSE;
	unref(str);
	unref(dest);

	return result;
}

/*
bool string_end_with(string str, string str1)
bool string_end_with(string str, char ch)
*/
FinCData* finc_string_end_with(Vector* v)
{
	FinCData* str;
	FinCData* dest;
	FinCData* result;
	FinCType* type;
	int l_result;
	char ch;
	unsigned char *p, *q;

	str = vector_at(v, 0);
	if (!str)return NULL;
	p = finc_access(str->raw, 0, unsigned char*);
	l_result = strlen(p);
	p = p + l_result;

	dest = vector_at(v, 1);
	if (!dest)
	{
		unref(str);
		return NULL;
	}

	type = finc_type_new(FinCType_Bool, FinCArrayType_None, 0);
	result = finc_data_new(type, NULL);
	unref(type);

	if (dest->type->type & FinCType_String)
	{
		q = finc_access(dest->raw, 0, unsigned char*);
		p = p + strlen(p) - strlen(q);
		if (strcmp(p, q)==0) l_result = 1;
	}
	else if ( dest->type->type & FinCType_Char )
	{
		ch = finc_access(dest->raw, 0, char);
		if (*p==ch) l_result = 1;
	}

	finc_access(result->raw, 0, Bool) = l_result;
	unref(str);
	unref(dest);

	return result;
}

/*
void string_toupper(string str)
*/
FinCData* finc_string_toupper(Vector* v)
{
	FinCData* str;

	str = vector_at(v, 0);
	if (!str)return NULL;

//	toupper(finc_access(str, 0, unsigned char*));

	unref(str);
	return NULL;
}

/*
void string_tolower(string str)
*/
FinCData* finc_string_tolower(Vector* v)
{
	FinCData* str;

	str = vector_at(v, 0);
	if (!str)return NULL;

//	tolower(finc_access(str, 0, unsigned char*));

	unref(str);
	return NULL;
}

/*
string[] string_splite(string str, string str1)
*/
FinCData* finc_string_splite(Vector* v)
{
	return NULL;
}

/*
string string_join(string str[], string str1)
*/
FinCData* finc_string_join(Vector* v)
{
	return NULL;
}

/*
viod finc_string_set_size(Vector* v)
*/
FinCData* finc_string_set_size(Vector* v)
{
	FinCData* str;
	FinCData* size;
	FinCData* char_array;
	FinCType* type;
	int length;

	str = (FinCData*)vector_at(v, 0);
	if (!str)return NULL;

	size = (FinCData*)vector_at(v, 1);
	if ( !str || !size )
	{
		unref(str);
		return NULL;
	}

	length = finc_access(size->raw, 0, int);
	if ( length <=0 )
	{
		unref(str);
		unref(size);
		return NULL;
	}

	type = finc_type_new(FinCType_Char, FinCArrayType_Fixed, length);
	char_array = finc_data_new(type, NULL);
	unref(type);

	finc_access(str->raw, 0, ADT) = char_array->raw;
	unref(str->pointer);
	str->pointer = char_array;

	unref(str);
	unref(size);

	return NULL;
}

#endif
