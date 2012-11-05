#ifndef _STR_H_
#define _STR_H_

#include <tiny/global.h>
#include <tiny/object.h>

typedef struct _String String;
struct _String
{
	Object parent;
	unsigned char* data;
};

String* string_new ();
String* string_new_str (unsigned char* text);

void string_destroy (String* self);

unsigned int string_hash(void* self);

void string_clear (String* self);

void string_set (String* self, String* p_text);

void string_set_str (String* self, unsigned char* p_text);

unsigned char string_at (String* self, int index);

Bool string_is_empty(String* self);

void string_add (String* self, String* p_text);

void string_add_str (String* self, unsigned char* p_text);

void string_add_char (String* self, signed char p_char);

signed int string_cmp (String* self, String* p_text);

signed int string_cmp_str (String* self, unsigned char* p_text);

Bool string_equal(void* self, void* other);

signed int string_ncmp (String* self, String* p_text, unsigned int p_pos, unsigned int p_size);

signed int string_ncmp_str (String* self, unsigned char* p_text, unsigned int p_pos, unsigned int p_size);

unsigned int string_get_size (String* self);

signed char string_get_char (String* self, unsigned int p_index);

unsigned char* string_get_str (String* self);

String* string_extract (String* self, unsigned int p_index, unsigned int p_size);

#endif
