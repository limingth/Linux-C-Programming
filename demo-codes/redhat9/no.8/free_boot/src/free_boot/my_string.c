/*
 *	my_string.c   - the base string operate
 *	
 *	Author: 	yu feng <progeryf@gmail.com>
 *	Date:		2007-5-11
 */


/*
 * int my_strlen(char *src)
 * get the length of the string src
 * input: src  -- the pointer of the sting
 * return the length of the string
 */
int my_strlen(const char *src)
{
	int length;

	length = 0;

	while (src[length++] != '\0');

	return length;
}

/*
 * int my_strcmp(char *src , char *dst)
 * compare the two strings
 * input: src -- the pointer of src, dst -- the pointer of dst
 * return: the result of src compare dst
 * 		  dst = src return 0
 * 		  dst > src return -n
 * 		  dst < src return n
 */
int my_strcmp(const char *dst , const char *src)
{
	
	while ( *src == *dst && *dst != '\0' )
	{
		src++;
		dst++;
	}
	return (*src - *dst); 
}

/*
 * int my_strcpy(char *dst, char *src )
 * copy string from src to dst 
 * input: src -- the pointer of src, dst -- the pointer of dst
 * return: 0
 */
int my_strcpy(char *dst, char *src)
{

	while (*dst++ = *src++);

	return 0;
}

/*
 * void* my_memcpy(const void *dst, void *src, int count)
 * copy one area from src to dst
 */
void* my_memcpy(const void *dst, void *src, int count)
{
	
	char *tmp = dst;
	const char *s = src;
	
	while (count--)
		*tmp++ = *s++;

	return dst;
}
/*
 * void* my_memset(void *dst, int c, int count)
 * set the dst to c from dst to dst+count
 */

void* my_memset(void *dst, int c, int count)
{
	char *s = dst;

	while (count--)
		*s++ = c;

	return dst;
}

unsigned my_atoi(char* src)
{
	unsigned tmp = 0;

	if (*src - '0' == 0 && *++src == 'x')
	{
		while (*src++ != '\0')
		{
			if (*src - '0' >= 0 && *src - '0' <= 9)
				tmp = tmp*16 + (*src - '0');	
			else if (*src - 'a' >= 0 && *src - 'a' <= 5)
				tmp = tmp*16 + 10 + (*src - 'a');
		}
		return tmp;
	}

	if (*src - '0' > 0 && *src - '0' <= 9)
	{
		while (*src != '\0')
		{
			if (*src - '0' >= 0 && *src - '0' <= 9)
				tmp = tmp*10 + (*src - '0');	
			src++;
		}
		return tmp;
	}
}
