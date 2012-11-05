#include <tiny/string.h>

String* string_new ()
{
	String* self;

	self = (String*)mem_new(sizeof(String));
	self->data = NULL;
	object_init_object (OBJECT (self), (ObjectDestroy) string_destroy);

	string_clear (self);

	return self;
}

String* string_new_str (unsigned char* text)
{
	String* self;

	self = string_new();
	string_set_str (self, text);

	return self;
}

void string_destroy (String* self)
{
	mem_destroy (self->data);
	mem_destroy (self);
}

unsigned int string_hash(void* self)
{
	const char *p;
	int h=0, g;

	for(p = ((String*)self)->data; *p != '\0'; p += 1)
	{
		h = ( h << 4 ) + *p;
		if ( ( g = h & 0xf0000000 ) )
		{
			h = h ^ (g >> 24);
			h = h ^ g;
		}
	}

	return h ;
}

void string_clear (String* self)
{
	string_set_str (self, "");
}

void string_set (String* self, String* p_text)
{
	string_set_str (self, p_text->data);
}

void string_set_str (String* self, unsigned char* p_text)
{
	if (p_text)
	{
		self->data = (unsigned char*) mem_resize (self->data, strlen (p_text) + 1);
		strcpy (self->data, p_text);
	}
}

unsigned char string_at (String* self, int index)
{
	return self->data[index];
}

Bool string_is_empty(String* self)
{
	return string_get_size(self) == 0? TRUE : FALSE;
}

void string_add (String* self, String* p_text)
{
	string_add_str (self, p_text->data);
}

void string_add_str (String* self, unsigned char* p_text)
{
	self->data = (unsigned char*) mem_resize (self->data, strlen (self->data) + strlen (p_text) + 1);
	strcat (self->data, p_text);
}

void string_add_char (String* self, signed char p_char)
{
	unsigned int l_size;

	l_size = string_get_size (self);
	self->data = (unsigned char*) mem_resize (self->data, l_size + 2);
	self->data[l_size] = p_char;
	self->data[l_size + 1] = '\0';
}

signed int string_cmp (String* self, String* p_text)
{
	return string_cmp_str (self, p_text->data);
}

signed int string_cmp_str (String* self, unsigned char* p_text)
{
	return strcmp (self->data, p_text);
}

Bool string_equal(ADT self, ADT other)
{
	return strcmp(((String*)self)->data, ((String*)other)->data)==0? TRUE:FALSE;
}

signed int string_ncmp (String* self, String* p_text, unsigned int p_pos, unsigned int p_size)
{
	return strncmp (self->data + p_pos, p_text->data, p_size);
}

signed int string_ncmp_str (String* self, unsigned char* p_text, unsigned int p_pos, unsigned int p_size)
{
	return strncmp (self->data + p_pos, p_text, p_size);
}

unsigned int string_get_size (String* self)
{
	if (self) return strlen (self->data);
	else return 0;
}

signed char string_get_char (String* self, unsigned int p_index)
{
	return self->data[p_index];
}

unsigned char* string_get_str (String* self)
{
	if (self)
		return self->data;
	else
		return NULL;
}

String* string_extract (String* self, unsigned int p_index, unsigned int p_size)
{
	String*	l_string;
	unsigned int i;

	l_string = string_new ();
	for (i = 0; i < p_size; i++)
		string_add_char (l_string, string_get_char (self, p_index + i));

	return l_string;
}
