#ifndef _FinC_TOKEN_H
#define _FinC_TOKEN_H

#include <ctype.h>

#include <tiny/object.h>
#include <tiny/string.h>

#include <finc/fincconfig.h>

//#define FINC_TOKEN_DEBUG

enum _FinCTokenType
{
	FinCTokenType_Left_Paren ,		/* (  */
	FinCTokenType_Right_Paren ,		/* )  */
	FinCTokenType_Left_Curly ,		/* {  */
	FinCTokenType_Right_Curly ,		/* }  */
	FinCTokenType_Left_Brace ,		/* [  */
	FinCTokenType_Right_Brace ,		/* ]  */
	FinCTokenType_Comma ,			/* ,  */
	FinCTokenType_Colon ,			/* :  */
	FinCTokenType_Scope ,			/* :: */
	FinCTokenType_Semicolon ,		/* ;  */
	FinCTokenType_Dot ,				/* .  */
	FinCTokenType_Question ,		/* ?  */
	FinCTokenType_Not ,				/* !  */
	FinCTokenType_Not_Eqs,			/* != */
	FinCTokenType_Mul ,				/* *  */
	FinCTokenType_Add ,				/* +  */
	FinCTokenType_Inc,				/* ++ */
	FinCTokenType_Sub ,				/* -  */
	FinCTokenType_Dec,				/* -- */
	FinCTokenType_Div ,				/* /  */
	FinCTokenType_Mod ,				/* %  */
	FinCTokenType_Assign ,			/* =  */
	FinCTokenType_Eq,				/* == */
	FinCTokenType_GT ,				/* >  */
	FinCTokenType_Greater_Eqs,		/* >= */
	FinCTokenType_LT ,				/* <  */
	FinCTokenType_Less_Eqs,			/* <= */
	FinCTokenType_Logic_And,		/* && */
	FinCTokenType_Logic_Or,			/* || */
	FinCTokenType_And,				/* & */
	FinCTokenType_Or,				/* | */
	FinCTokenType_XOR,				/* ^ */
	FinCTokenType_Bitwise,			/* ~ */
	FinCTokenType_SHL,				/* << */
	FinCTokenType_SHR,				/* >> */
	/*--literal--*/
	FinCTokenType_Char, 			/* char        */
	FinCTokenType_String, 			/* string      */
	FinCTokenType_Short,			/* short       */
	FinCTokenType_Int,				/* int         */
	#ifdef USING_FLOAT
	FinCTokenType_Float,			/* float       */
	#endif
	#ifdef USING_DOUBLE
	FinCTokenType_Double,			/* double      */
	#endif
	FinCTokenType_Long,				/* long        */
	/*--data type--*/
	FinCTokenType_Type_Void,		/* void type   */
	FinCTokenType_Type_Int,			/* int type    */
	FinCTokenType_Type_Char,		/* char type   */
	FinCTokenType_Type_Short,		/* short type  */
	#ifdef USING_DOUBLE
	FinCTokenType_Type_Double,		/* double type */
	#endif
	#ifdef USING_LONG
	FinCTokenType_Type_Long,		/* long type */
	#endif
	#ifdef USING_FLOAT
	FinCTokenType_Type_Float,		/* float type  */
	#endif
	FinCTokenType_Type_Bool,		/* bool type   */
	FinCTokenType_Type_Pointer,		/* pointer type*/
	FinCTokenType_Type_String,		/* string type */

	/*--key word--*/
	FinCTokenType_Static, 			/* static      */
	FinCTokenType_Unsigned,			/* unsigned    */
	FinCTokenType_Struct,			/* struct      */
	#ifdef USING_OO
	FinCTokenType_Class,			/* class       */
	FinCTokenType_Public,			/* public      */
	FinCTokenType_Private,			/* private     */
	FinCTokenType_This,				/* this        */
	#endif
	FinCTokenType_False,			/* false       */
	FinCTokenType_True, 			/* true        */
	FinCTokenType_Null,				/* null        */
	FinCTokenType_For,				/* for         */
	FinCTokenType_While, 			/* while       */
	FinCTokenType_If,				/* if          */
	FinCTokenType_Else,				/* else        */
	FinCTokenType_Return, 			/* return      */
	FinCTokenType_Break,			/* break       */
	FinCTokenType_Continue,			/* continute   */
	FinCTokenType_Import,			/* import      */
	FinCTokenType_Package,			/* package     */
	FinCTokenType_Addrof,			/* addrof      */
	FinCTokenType_Valueof,			/* valueof     */
	FinCTokenType_Identifier,		/* ID          */
	FinCTokenType_Eof,
	FinCTokenType_Bad
};
typedef enum _FinCTokenType FinCTokenType;

typedef struct _FinCTokenEnv FinCTokenEnv;
struct _FinCTokenEnv
{
	Object parent;

	Bool eof;
	Bool replay;

	int line;
	int position;

	FinCTokenType current_token;

	String* line_str;

	String* last_str;
	char last_char;
	#ifdef USING_LONG_DOUBLE
	long double last_double;
	#else
	long last_double;
	#endif
	float last_float;
	long last_long;

	unsigned char* (*read_line)(const char* arg);
	const char* arg;
};

FinCTokenEnv* finc_token_new();
void finc_token_destroy(Object* self);

FinCTokenType finc_token_token(FinCTokenEnv* self);
String* finc_token_get_token(FinCTokenEnv* self);

#ifdef FINC_TOKEN_DEBUG
void finc_token_debug(FinCTokenEnv* token);
void finc_token_expect(FinCTokenType token);
#endif

#define finc_token_line(self) (self)->line
#define finc_token_position(self) (self)->position
#define finc_token_replay(self) (self)->replay = TRUE

#endif
