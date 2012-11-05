#define	NULL	0
#define	STATUS_ERR	1
#define	STATUS_OK		0
typedef	void (* PrVoid)(void);
typedef	PrVoid (*PrPrVoid)(void);
	
typedef	unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef	signed char S8;
typedef signed short S16;
typedef signed int S32;

typedef	unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned int		DWORD;

typedef struct{
	U16 year;
	U8 month;
	U8 day;
	U8 weekday;
	U8 hour;
	U8 min;
	U8 sec;
}TIME_STRUC;

