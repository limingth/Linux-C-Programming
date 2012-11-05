#ifndef MY_STRING_H
#define MY_STRING_H

/*
 * int strlen(char *src)
 * get the length of the string src
 * input  : src  -- the pointer of the sting
 *
 */
int my_strlen(const char *src);

/*
 * int strcmp(char *src , char *dst)
 * compare the two strings
 *
 */
int my_strcmp(const char *src, const char *dst);

/*
 *
 */
int my_strcpy(char *src , char *dst);


void* my_memcpy(const void *dst, void *src, int count);
void* my_memset(void *dst, int c, int count);
unsigned my_atoi(char* src);
#endif
