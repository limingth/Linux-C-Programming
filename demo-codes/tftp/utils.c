#include "utils.h"


void memcpy(void *s1, const void *s2, int n)
{
	int i;

	for (i = 0; i < n; i++)
		((char *)(s1))[i] = ((const char *)(s2))[i];
}

void memset(void *s, const char ch, int n)
{
	int i;

	for (i = 0; i < n; i++)
		((char *)(s))[i] = ch;
}

unsigned short ntohs(unsigned short s)
{
	return (s >> 8) | (s << 8);
}

unsigned long ntohl(unsigned long l)
{
	return  ((l >> 24) & 0x000000ff) |
		((l >>  8) & 0x0000ff00) |
		((l <<  8) & 0x00ff0000) |
		((l << 24) & 0xff000000);
}

unsigned short htons(unsigned short s)
{
	return (s >> 8) | (s << 8);
}

unsigned long htonl(unsigned long l)
{
	return  ((l >> 24) & 0x000000ff) |
		((l >>  8) & 0x0000ff00) |
		((l <<  8) & 0x00ff0000) |
		((l << 24) & 0xff000000);
}

unsigned long strtoul(char *s, char **endptr, int radix)
{
	unsigned long ret;
	int i;

	ret = 0;

	while (*s != '\0') {
		if (*s >= '0' && *s <= '9')
			i = *s - '0';
		else if (*s >= 'a' && *s <= 'f')
			i = *s - 'a' + 0xa;
		else if (*s >= 'A' && *s <= 'F')
			i = *s - 'A' + 0xa;
		else
			return -1;
		ret = (ret << 4) + i;
		s++;
	}

	return ret;
}

void ultostr(char *s, unsigned long data)
{
	int i;
	
	s[8] = 0;
	for(i=7; i>=0; i--, data>>=4)
	{		
		if((data&0xf)<=9)
			s[i] = (data&0xf)+'0';
		else
			s[i] = (data&0xf)+'a'-0xa;
	}	
}

unsigned long CharToDec(char *str, int cnt)
{
	unsigned long i, data = 0;	
	
	for(i=0; i<cnt; i++)
	{
		data *= 10;
		if(str[i]<'0'||str[i]>'9')
			return -1;
		data += str[i]-'0';			
	}	
	return data;
}

int strlen(const char *s)
{
	int i = 0;

	for(;*s != '\0'; s++)
		i++;
	
	return i;
}

int strncmp(const char *s1, const char *s2, int maxlen) 
{
	int i;

	for(i = 0; i < maxlen; i++) {
		if(s1[i] != s2[i])
			return ((int) s1[i]) - ((int) s2[i]);
		if(s1[i] == 0)
			return 0;
	}

	return 0;
}
