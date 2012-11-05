#include <finc/finctoken.h>
#include <finc/finclang.h>
#include <finc/finccontext.h>

#define is_digit(ch)	((ch) >= '0' && (ch) <= '9')
#define is_separator(ch) !(((ch) >= 'a' && (ch) <= 'z') \
     || ((ch) >= 'A' && (ch) <= 'Z') || ((ch) >= '0' && (ch) <= '9') || ((ch) == '_'))
#define is_eof(self) (self)->eof

#ifdef FINC_DEBUG
#define	HERE	kprintf("here, %s:%d\n", __FILE__, __LINE__)
#else
#define HERE
#endif

typedef struct _NameTable NameTable;
struct _NameTable
{
	char* name;
	FinCTokenType type;
};

static NameTable name_table[] =
{
	{"void",		FinCTokenType_Type_Void},
	{"int",			FinCTokenType_Type_Int},
	{"char",		FinCTokenType_Type_Char},
	{"short",		FinCTokenType_Type_Short},
	#ifdef USING_DOUBLE
	{"double",		FinCTokenType_Type_Double},
	#endif
	#ifdef USING_LONG
	{"long",		FinCTokenType_Type_Long},
	#endif
	#ifdef USING_FLOAT
	{"float",		FinCTokenType_Type_Float},
	#endif
	{"bool",		FinCTokenType_Type_Bool},
	{"pointer",		FinCTokenType_Type_Pointer},
	{"string",		FinCTokenType_Type_String},
	{"static",		FinCTokenType_Static},
	{"unsigned",	FinCTokenType_Unsigned},
	{"struct",		FinCTokenType_Struct},
	{"false",		FinCTokenType_False},
	{"true",		FinCTokenType_True},
	{"null",		FinCTokenType_Null},
	{"for",			FinCTokenType_For},
	{"while",		FinCTokenType_While},
	{"if",			FinCTokenType_If},
	{"else",		FinCTokenType_Else},
	{"return",		FinCTokenType_Return},
	{"break",		FinCTokenType_Break},
	{"continue",	FinCTokenType_Continue},
	{"import",		FinCTokenType_Import},
	{"package",	    FinCTokenType_Package},
	{"addrof",		FinCTokenType_Addrof},
	{"valueof",		FinCTokenType_Valueof}
};

static String* token_get_string(FinCTokenEnv* self);
static void token_run(FinCTokenEnv* self);
static Bool token_match_name(FinCTokenEnv* self, const char* str);
static void token_trim_comment(FinCTokenEnv* self);
static void token_trim_line_comment(FinCTokenEnv* self);
static void token_trim_space(FinCTokenEnv* self);
static char token_proc_char(FinCTokenEnv* self);
static String* token_proc_string(FinCTokenEnv* self);
static void token_proc_number(FinCTokenEnv* self);
#ifdef USING_DOUBLE
static double token_spec_number(char* string, int length, int b);
#else
static long token_spec_number(char* string, int length, int b);
#endif
static int token_proc_escape(FinCTokenEnv* self);

static char token_next_char(FinCTokenEnv* self);
static void token_prev_char(FinCTokenEnv* self);

FinCTokenEnv* finc_token_new()
{
	FinCTokenEnv* self;

	self = (FinCTokenEnv*)mem_new (sizeof(FinCTokenEnv));
	object_init_object (OBJECT (self), finc_token_destroy);

	self->eof = FALSE;
	self->replay = FALSE;

	self->line = 0;
	self->position = 0;

	self->current_token = FinCTokenType_Bad;

	self->line_str = NULL;

	self->last_str = NULL;
	self->last_char = '\0';
	self->last_double = 0;
	#ifdef USING_FLOAT
	self->last_float = 0;
	#endif
	self->last_long = 0;

	return self;
}

void finc_token_destroy(Object* self)
{
	FinCTokenEnv* real;

	real = (FinCTokenEnv*)self;

	unref(real->line_str);
	unref(real->last_str);

	mem_destroy(self);
}

FinCTokenType finc_token_token(FinCTokenEnv* self)
{
	if ( self->replay )
		self->replay = FALSE;
	else
	{
		token_run(self);
#ifdef FINC_TOKEN_DEBUG
		finc_token_debug(self);kprintf(" ");
#endif
	}
	return self->current_token;
}

String* finc_token_get_token(FinCTokenEnv* self)
{
	return addref(String, self->last_str);
}

String* token_get_string(FinCTokenEnv* self)
{
	char str[80];/*the max identifier length is 80*/
	char *p=str;
	char ch;
	
	ch = token_next_char(self);
	if (is_eof(self))return NULL;

	str[0] = '\0';

	if ( is_digit(ch) )/*the first character of identifier is not a digit.*/
	{
		token_prev_char(self);
		return NULL;
	}

	while ( !is_separator(ch)&&!is_eof(self) )
	{
		*p = ch;
		ch = token_next_char(self);
		p++;
	}
	self->eof = FALSE;

	token_prev_char(self);
	*p = '\0';

	return string_new_str(str);
}

/*
get next character.
*/
static char token_next_char(FinCTokenEnv* self)
{
	if (self->eof) return '\0';
	if ( self->position == string_get_size( self->line_str ) )
	{
		unref(self->line_str);
		self->line_str = string_new_str( (*self->read_line)(self->arg) );

		HERE;
		if (string_is_empty(self->line_str))
		{
			HERE;
			self->eof = TRUE;
			self->position = 0;
			return '\0';
		}

		self->line++;
#ifdef FINC_TOKEN_DEBUG
		kprintf("\n");
#endif
		self->position = 0;
		return token_next_char(self);
	}
	else if ( string_at(self->line_str, self->position) =='\n' )
	{
		unref(self->line_str);
		self->line_str = string_new_str( (*self->read_line)(self->arg) );
		HERE;
		if (string_is_empty(self->line_str))
		{
			HERE;
			self->eof = TRUE;
			self->position = 0;
			return '\0';
		}
		self->line++;
#ifdef FINC_TOKEN_DEBUG
		kprintf("\n");
#endif
		self->position = 0;
		return token_next_char(self);
	}
	else
	{
		return string_at( self->line_str, self->position++);
	}
}

static void token_prev_char(FinCTokenEnv* self)
{
	if ( self->eof ) return;
	if ( self->position == 0 )
	{
		return;
	}

	self->position--;
}

static void token_run(FinCTokenEnv* self)
{
	char ch;

	token_trim_space(self);/*first trim space and tab.*/

	unref(self->last_str);
	self->last_str = token_get_string(self);/*get the last string( identifier or key word ).*/

	if ( is_eof(self) )/*if it is eof, break;*/
	{
		self->current_token = FinCTokenType_Eof;
		return ;
	}

	if ( !string_is_empty(self->last_str) )/*It is a key word or a identifier.*/
	{
		if ( !token_match_name(self, string_get_str (self->last_str)) )
		{
			self->current_token = FinCTokenType_Identifier;
		}
		return;
	}
	else/*It is a operator character.*/
	{
		ch = token_next_char(self);

		switch ( ch )
		{
		case '(':
			self->current_token = FinCTokenType_Left_Paren;
			break;

		case ')':
			self->current_token = FinCTokenType_Right_Paren;
			break;

		case '{':
			self->current_token = FinCTokenType_Left_Curly;
			break;

		case '}':
			self->current_token = FinCTokenType_Right_Curly;
			break;

		case '[':
			self->current_token = FinCTokenType_Left_Brace;
			break;

		case ']':
			self->current_token = FinCTokenType_Right_Brace;
			break;

		case ',':
			self->current_token = FinCTokenType_Comma;
			break;

		case ':':
			self->current_token = FinCTokenType_Colon;
			break;

		case ';':
			self->current_token = FinCTokenType_Semicolon;
			break;

		case '?':
			self->current_token = FinCTokenType_Question;
			break;

		case '!':
			ch = token_next_char(self);

			if ( ch == '=' )
			{
				self->current_token = FinCTokenType_Not_Eqs;
			}
			else
			{
				token_prev_char(self);
				self->current_token = FinCTokenType_Not;
			}
			break;

		case '&':
			ch = token_next_char(self);

			if ( ch == '&' )
			{
				self->current_token = FinCTokenType_Logic_And;
			}
			else
			{
				self->current_token = FinCTokenType_And;
				token_prev_char(self);
			}
			break;

		case '*':
			self->current_token = FinCTokenType_Mul;
			break;

		case '+':
			ch = token_next_char(self);

			if ( ch == '+' )
			{
				self->current_token = FinCTokenType_Inc;
			}
			else
			{
				token_prev_char(self);
				self->current_token = FinCTokenType_Add;
			}
			break;

		case '-':
			ch = token_next_char(self);

			if ( ch == '-' )
			{
				self->current_token = FinCTokenType_Dec;
			}
			else
			{
				token_prev_char(self);
				self->current_token = FinCTokenType_Sub;
			}
			break;

		case '/':
			self->current_token = FinCTokenType_Div;
			break;

		case '<':
			ch = token_next_char(self);

			if ( ch == '=' )
			{
				self->current_token = FinCTokenType_Less_Eqs;
			}
			else if ( ch == '<' )
			{
				self->current_token = FinCTokenType_SHL;
			}
			else
			{
				token_prev_char(self);
				self->current_token = FinCTokenType_LT;
			}
			break;

		case '>':
			ch = token_next_char(self);

			if ( ch == '=' )
			{
				self->current_token = FinCTokenType_Greater_Eqs;
			}
			else if ( ch == '>' )
			{
				self->current_token = FinCTokenType_SHR;
			}
			else
			{
				token_prev_char(self);
				self->current_token = FinCTokenType_GT;
			}
			break;

		case '|':
			ch = token_next_char(self);

			if ( ch == '|' )
			{
				self->current_token = FinCTokenType_Logic_Or;
			}
			else
			{
				self->current_token = FinCTokenType_Or;
				token_prev_char(self);
			}
			break;

		case '%':
			self->current_token = FinCTokenType_Mod;
			break;

		case '~':
			self->current_token = FinCTokenType_Bitwise;
			break;

		case '^':
			self->current_token = FinCTokenType_XOR;
			break;
		
		case '=':
			ch = token_next_char(self);

			if ( ch =='=' )
			{
				self->current_token = FinCTokenType_Eq;
			}
			else
			{
				token_prev_char(self);
				self->current_token = FinCTokenType_Assign;
			}
			break;

		case '\'':
			self->last_char = token_proc_char(self);
			self->current_token = FinCTokenType_Char;
			break;

		case '"':
			unref(self->last_str);
			self->last_str = NULL;
			self->last_str = token_proc_string(self);
			self->current_token = FinCTokenType_String;
			break;

		case '.':
			ch = token_next_char(self);
			if ( is_digit(ch) )/*if it's a float number.*/
			{
				token_proc_number(self);
				break;
			}
			else
			{
				token_prev_char(self);
				self->current_token = FinCTokenType_Dot;
			}
			break;

		default:
			if ( is_digit(ch) )
			{
				token_prev_char(self);
				token_proc_number(self);
				break;
			}
			kprintf ( "Lex Error: Unknown characector\n");
			finc_context_error_inc(g_finc_context);
			self->current_token = FinCTokenType_Bad;

			break;
		}
	}
}

static Bool token_match_name(FinCTokenEnv* self, const char* str)
{
	int i;
	for ( i=0; i<sizeof(name_table)/sizeof(*name_table); i++)
	{
		if ( strcmp(name_table[i].name, str)==0 )
		{
			self->current_token = name_table[i].type;
			return TRUE;
		}
	}
	return FALSE;
}

static void token_trim_comment(FinCTokenEnv* self)
{
	char ch;
	while( !is_eof(self) )
	{
		ch = token_next_char(self);
		if ( ch =='*' )
		{
			ch = token_next_char(self);
			if ( ch =='/' )
				return;
			token_prev_char(self);
		}
	}

	kprintf( "Lex Error: Unexpecting end of comment.\n");
	finc_context_error_inc(g_finc_context);
}

static void token_trim_line_comment(FinCTokenEnv* self)
{
	unref(self->line_str);
	self->line_str = string_new_str( (*self->read_line)(self->arg) );
	if (string_is_empty(self->line_str)) self->eof = TRUE;

	self->line++;
	self->position = 0;
}

static void token_trim_space(FinCTokenEnv* self)
{
	char ch;
	while ( (ch = token_next_char(self)) ==' ' || ch == '\t' || ch == '/' )
	{
		if ( ch == '/' )
		{
			ch = token_next_char(self);
			if ( ch == '*' )
			{
				token_trim_comment(self);
			}
			else if ( ch == '/' )
			{
				token_trim_line_comment(self);
			}
			else
			{
				token_prev_char(self);
				break;
			}
		}
	}

	token_prev_char(self);
}

static char token_proc_char(FinCTokenEnv* self)
{
	char ch;
	char buf[4], *p;

	p = buf;
	ch = token_next_char(self);

	if ( ch == '\\' )
	{
		ch = token_next_char(self);
		switch ( ch )
		{
		case 'n': ch = '\n'; break;
		case 't': ch = '\t'; break;
		case 'v': ch = '\v'; break;
		case 'b': ch = '\b'; break;
		case 'r': ch = '\r'; break;
		case '\\': ch = '\\';  break;
		case '\'': ch = '\'';  break;
		default :
			while ( is_digit(ch) )/*for '\113' char*/
			{
				ch = token_next_char(self);
				*p++ = ch;
			}

			token_prev_char(self);
			*p = '\0';
			ch = atoi(p);
			break;
		}
	}

	if ( token_next_char(self) != '\'' )
	{
		token_prev_char(self);
		kprintf( "Lex Error: Expecting a '\''.\n");
		finc_context_error_inc(g_finc_context);
		return ch;
	}

	return ch;
}

static String* token_proc_string(FinCTokenEnv* self)
{
	String* string;

	string = string_new();
	for ( ; ; )
	{
		char ch = token_next_char(self);

		if ( is_eof(self) )
		{
			kprintf( "Lex Error: Unexpecting end in process string.\n");
			finc_context_error_inc(g_finc_context);
			unref(string);

			return NULL;;
		}
		if ( ch == '\\' )
		{
			ch = token_proc_escape(self);
		}
		else if ( ch == '"' )/*end of string.*/
		{
			unref(self->last_str);
			self->last_str = string;
			return string;
		}
		string_add_char(string, ch);
	}

	return string;
}

static int token_proc_escape(FinCTokenEnv* self)
{
	char ch;
	int result=0;

	ch = token_next_char(self);
	switch (ch)
	{
	case 'n':
		result = '\n';
		break;
	case 't':
		result = '\t';
		break;
	case 'v':
		result = '\v';
		break;
	case 'b':
		result = '\b';
		break;
	case 'r':
		result = '\r';
		break;
	case 'f':
		result = '\f';
		break;
	case 'a':
		result = '\007';
		break;
	case 'x':
		result = 0;
		ch  = token_next_char(self);
		while ( (ch - '0')<16u )
		{
			result = result*16 + ch - '0';
			ch = token_next_char(self);
		}
		token_prev_char(self);
		break;
	default:
		if ( (ch - '0') < 8u)
		{
			result = 0;
			while ( (ch - '0') < 8u )
			{
				result = result*8 + ch - '0';
				ch = token_next_char(self);
			}

			token_prev_char(self);
		}
		break;
	}

	return result;
}

/*
(0|0x|0X|0b|0B)number+((.)number+)(e|E)(+|-)number+(f|F|l|L|u|U)
*/
static void token_proc_number(FinCTokenEnv* self)
{
	char ch;
	int b;
	char *p, buf[128];
	#ifdef USING_LONG_DOUBLE
	long double factor;
	#else
	float factor;
	#endif
	unsigned int expo;
	int sign;
	#ifdef USING_LONG_DOUBLE
	long double value;
	#else
	float value;
	#endif

	sign = +1;
	value = 0.L;
	p = buf;
	b = 10;
	factor = 0.0;

	ch  = token_next_char(self);
	if ( ch == '0' )
	{
		ch = token_next_char(self);
		if ( ch == 'x' || ch == 'X' )/*it's a hex number*/
		{
			b = 16;
			ch = token_next_char(self);
			while ( is_digit(ch) || isalpha(ch) )
			{
				*p++ = ch;
				ch = token_next_char(self);
			}

			*p = '\0';
		}
		else if ( ch == 'b' || ch == 'B' )
		{
			b = 2;
			ch = token_next_char(self);
			while ( (ch=='0')||(ch=='1') )
			{
				*p++ = ch;
				ch = token_next_char(self);
			}

			*p = '\0';
		}
		else if ( ch == '.' )
		{
			goto float_label;
		}
		else
		{
			b = 8;
			while ( is_digit(ch) )
			{
				*p++ = ch;
				ch = token_next_char(self);
			}

			*p = '\0';
		}

		self->last_double = token_spec_number(buf, strlen(buf), b);
		self->current_token = FinCTokenType_Int;
	}
	else
	{
		while ( is_digit(ch) )
		{
			value = value*10 + ( ch - '0' );
			ch = token_next_char(self);
		}

		if ( ch == '.' )
		{
float_label:
			factor = 1.0;

			ch = token_next_char(self);
			while ( is_digit(ch) )
			{
				factor *= 0.1;
				value += ( ch - '0' )*factor;
				ch = token_next_char(self);
			}
		}

		if ( ch == 'e' || ch == 'E' )
		{
			expo = 0;
			factor = 10.L;

			ch = token_next_char(self);
			switch (ch)
			{
			case '-': factor = 0.1;
			case '+':
				ch = token_next_char(self);
				break;
			default:
				if ( is_digit(ch) ) break;
				else
				{
					value = 0.L;
					goto done;
				}
			}

			while ( is_digit(ch) )
			{
				expo = 10*expo + (ch - '0' );
				ch = token_next_char(self);
			}

			while (1)
			{
				if (expo & 1) value *= factor;
				if ((expo >>=1) == 0) break;
				factor *= factor;
			}
		}

done:
		self->last_double = value;
		#ifdef USING_FLOAT
		if (factor != 0.0) 
		{
			self->last_float = value;
			self->current_token = FinCTokenType_Float;
		}
		else
		#endif
		{
			self->current_token = FinCTokenType_Int;
		}
	}

	switch ( ch )
	{
	#ifdef USING_FLOAT
	case 'f':
	case 'F':
		self->current_token = FinCTokenType_Float;
		break;
	#endif

	case 'l':
	case 'L':
		self->current_token = FinCTokenType_Long;
		break;
	
	#ifdef USING_DOUBLE
	case 'd':
	case 'D':
		self->current_token = FinCTokenType_Double;
		break;
	#endif
	default:
		token_prev_char(self);
		break;
	}
}

/*use 64 bit number*/
#define BN_SIZE 2

#ifdef USING_DOUBLE
static double token_spec_number(char* string, int length, int b)
#else
static long token_spec_number(char* string, int length, int b)
#endif
{
	char* p;
	int t;
	int i, j, shift=1;
	unsigned int bn[BN_SIZE], v;
	#ifdef USING_DOUBLE
	double d;
	#else
	long d;
	#endif

	p = string;
	i = 0;

	switch ( b )
	{
	case 16: shift = 4;
		break;
	case 8:  shift = 3;
		break;
	case 2:  shift = 1;
		break;
	default: break;
	}

	for ( j=0; j<BN_SIZE ; j++) bn[j] = 0;

	while ( i<length )
	{
		t = *p++;
		if ( t>='a' && t <='f' )
		{
			t = t - 'a' +10;
		}
		else if ( t >='A' && t <='F' )
		{
			t = t - 'A' +10;
		}
		else t = t - '0';

		for ( j=0; j<BN_SIZE ; j++)
		{
			v = bn[j];
			bn[j] = (v<<shift) | t;
			t = v >> (32 - shift);
		}
		i++;
	}

	#ifdef USING_DOUBLE
	d = (double)bn[1] * 4294967296.0 + (double)bn[0];
	#else
	d = (long)bn[0];
	#endif

	return d;
}

#ifdef FINC_TOKEN_DEBUG
void finc_token_debug(FinCTokenEnv* token)
{
	switch (token->current_token)
	{
	case FinCTokenType_Left_Paren :
	kprintf("(");
	break;
	case FinCTokenType_Right_Paren :
	kprintf(")");
	break;
	case FinCTokenType_Left_Curly :
	kprintf("{");
	break;
	case FinCTokenType_Right_Curly :
	kprintf("}");
	break;
	case FinCTokenType_Left_Brace :
	kprintf("[");
	break;
	case FinCTokenType_Right_Brace :
	kprintf("]");
	break;
	case FinCTokenType_Comma :
	kprintf(",");
	break;
	case FinCTokenType_Colon :
	kprintf(":");
	break;
	case FinCTokenType_Semicolon :
	kprintf(";");
	break;
	case FinCTokenType_Dot :
	kprintf(".");
	break;
	case FinCTokenType_Question :
	kprintf("?");
	break;
	case FinCTokenType_Not :
	kprintf("!");
	break;
	case FinCTokenType_Not_Eqs:
	kprintf("!=");
	break;
	case FinCTokenType_And:
	kprintf("&");
	break;
	case FinCTokenType_Logic_And:
	kprintf("&&");
	break;
	case FinCTokenType_Mul :
	kprintf("*");
	break;
	case FinCTokenType_Add :
	kprintf("+");
	break;
	case FinCTokenType_Inc:
	kprintf("++");
	break;
	case FinCTokenType_Sub :
	kprintf("-");
	break;
	case FinCTokenType_Dec:
	kprintf("--");
	break;
	case FinCTokenType_Div :
	kprintf("/");
	break;
	case FinCTokenType_Mod :
	kprintf("mod");
	break;
	case FinCTokenType_Assign :
	kprintf("=");
	break;
	case FinCTokenType_Eq:
	kprintf("=");
	break;
	case FinCTokenType_GT :
	kprintf(">");
	break;
	case FinCTokenType_Greater_Eqs:
	kprintf(">=");
	break;
	case FinCTokenType_LT :
	kprintf("<");
	break;
	case FinCTokenType_Less_Eqs:
	kprintf("<=");
	break;
	case FinCTokenType_Logic_Or:
	kprintf("||");
	break;
	case FinCTokenType_Or:
	kprintf("|");
	break;
	case FinCTokenType_Char:
	kprintf("char");
	break;
	case FinCTokenType_Short:
	kprintf("short");
	break;
	case FinCTokenType_String:
	kprintf("string");
	break;
	case FinCTokenType_Int:
	kprintf("int");
	break;
	#ifdef USING_FLOAT
	case FinCTokenType_Float:
	kprintf("float");
	break;
	#endif
	#ifdef USING_DOUBLE
	case FinCTokenType_Double:
	kprintf("double");
	break;
	#endif
	case FinCTokenType_Long:
	kprintf("long");
	break;
	case FinCTokenType_Type_Void:
	kprintf("void");
	break;
	case FinCTokenType_Type_Int:
	kprintf("type:int");
	break;
	case FinCTokenType_Type_Char:
	kprintf("type:char");
	break;
	case FinCTokenType_Type_Short:
	kprintf("type:short");
	break;
	#ifdef USING_DOUBLE
	case FinCTokenType_Type_Double:
	kprintf("type:double");
	break;
	#endif
	#ifdef USING_FLOAT
	case FinCTokenType_Type_Float:
	kprintf("type:float");
	break;
	#endif
	case FinCTokenType_Type_Bool:
	kprintf("type:bool");
	break;
	case FinCTokenType_Type_Pointer:
	kprintf("type:pointer");
	break;
	case FinCTokenType_Type_String:
	kprintf("type:string");
	break;
	case FinCTokenType_Static:
	kprintf("static");
	break;
	case FinCTokenType_Unsigned:
	kprintf("unsigned");
	break;
	case FinCTokenType_Struct:
	kprintf("struct");
	break;
	case FinCTokenType_False:
	kprintf("false");
	break;
	case FinCTokenType_True:
	kprintf("true");
	break;
	case FinCTokenType_Null:
	kprintf("null");
	break;
	case FinCTokenType_For:
	kprintf("for");
	break;
	case FinCTokenType_While:
	kprintf("while");
	break;
	case FinCTokenType_If:
	kprintf("if");
	break;
	case FinCTokenType_Else:
	kprintf("else");
	break;
	case FinCTokenType_Return:
	kprintf("return");
	break;
	case FinCTokenType_Break:
	kprintf("break");
	break;
	case FinCTokenType_Continue:
	kprintf("continue");
	break;
	case FinCTokenType_Import:
	kprintf("import");
	break;
	case FinCTokenType_Package:
	kprintf("package");
	break;
	case FinCTokenType_Addrof:
	kprintf("addrof");
	break;
	case FinCTokenType_Valueof:
	kprintf("valueof");
	break;
	case FinCTokenType_Identifier:
	kprintf("id");
	break;
	case FinCTokenType_Eof:
	kprintf("eof\n");
	break;
	case FinCTokenType_Bad:
	kprintf("bad");
	break;
	}
}

void finc_token_expect(FinCTokenType token)
{
	switch (token)
	{
	case FinCTokenType_Left_Paren :
	kprintf("(");
	break;
	case FinCTokenType_Right_Paren :
	kprintf(")");
	break;
	case FinCTokenType_Left_Curly :
	kprintf("{");
	break;
	case FinCTokenType_Right_Curly :
	kprintf("}");
	break;
	case FinCTokenType_Left_Brace :
	kprintf("[");
	break;
	case FinCTokenType_Right_Brace :
	kprintf("]");
	break;
	case FinCTokenType_Comma :
	kprintf(",");
	break;
	case FinCTokenType_Colon :
	kprintf(":");
	break;
	case FinCTokenType_Semicolon :
	kprintf(";");
	break;
	case FinCTokenType_Dot :
	kprintf(".");
	break;
	case FinCTokenType_Question :
	kprintf("?");
	break;
	case FinCTokenType_Not :
	kprintf("!");
	break;
	case FinCTokenType_Not_Eqs:
	kprintf("!=");
	break;
	case FinCTokenType_And:
	kprintf("&");
	break;
	case FinCTokenType_Logic_And:
	kprintf("&&");
	break;
	case FinCTokenType_Mul :
	kprintf("*");
	break;
	case FinCTokenType_Add :
	kprintf("+");
	break;
	case FinCTokenType_Inc:
	kprintf("++");
	break;
	case FinCTokenType_Sub :
	kprintf("-");
	break;
	case FinCTokenType_Dec:
	kprintf("--");
	break;
	case FinCTokenType_Div :
	kprintf("/");
	break;
	case FinCTokenType_Mod :
	kprintf("mod");
	break;
	case FinCTokenType_Assign :
	kprintf("=");
	break;
	case FinCTokenType_Eq:
	kprintf("=");
	break;
	case FinCTokenType_GT :
	kprintf(">");
	break;
	case FinCTokenType_Greater_Eqs:
	kprintf(">=");
	break;
	case FinCTokenType_LT :
	kprintf("<");
	break;
	case FinCTokenType_Less_Eqs:
	kprintf("<=");
	break;
	case FinCTokenType_Logic_Or:
	kprintf("||");
	break;
	case FinCTokenType_Or:
	kprintf("|");
	break;
	case FinCTokenType_Char:
	kprintf("char");
	break;
	case FinCTokenType_Short:
	kprintf("short");
	break;
	case FinCTokenType_String:
	kprintf("string");
	break;
	case FinCTokenType_Int:
	kprintf("int");
	break;
	#ifdef USING_FLOAT
	case FinCTokenType_Float:
	kprintf("float");
	break;
	#endif
	#ifdef USING_DOUBLE
	case FinCTokenType_Double:
	kprintf("double");
	break;
	#endif
	case FinCTokenType_Long:
	kprintf("long");
	break;
	case FinCTokenType_Type_Void:
	kprintf("void");
	break;
	case FinCTokenType_Type_Int:
	kprintf("type:int");
	break;
	case FinCTokenType_Type_Char:
	kprintf("type:char");
	break;
	case FinCTokenType_Type_Short:
	kprintf("type:short");
	break;
	#ifdef USING_DOUBLE
	case FinCTokenType_Type_Double:
	kprintf("type:double");
	break;
	#endif
	#ifdef USING_FLOAT
	case FinCTokenType_Type_Float:
	kprintf("type:float");
	break;
	#endif
	case FinCTokenType_Type_Bool:
	kprintf("type:bool");
	break;
	case FinCTokenType_Type_Pointer:
	kprintf("type:pointer");
	break;
	case FinCTokenType_Type_String:
	kprintf("type:string");
	break;
	case FinCTokenType_Static:
	kprintf("static");
	break;
	case FinCTokenType_Unsigned:
	kprintf("unsigned");
	break;
	case FinCTokenType_Struct:
	kprintf("struct");
	break;
	case FinCTokenType_False:
	kprintf("false");
	break;
	case FinCTokenType_True:
	kprintf("true");
	break;
	case FinCTokenType_Null:
	kprintf("null");
	break;
	case FinCTokenType_For:
	kprintf("for");
	break;
	case FinCTokenType_While:
	kprintf("while");
	break;
	case FinCTokenType_If:
	kprintf("if");
	break;
	case FinCTokenType_Else:
	kprintf("else");
	break;
	case FinCTokenType_Return:
	kprintf("return");
	break;
	case FinCTokenType_Break:
	kprintf("break");
	break;
	case FinCTokenType_Continue:
	kprintf("continue");
	break;
	case FinCTokenType_Import:
	kprintf("import");
	break;
	case FinCTokenType_Package:
	kprintf("package");
	break;
	case FinCTokenType_Addrof:
	kprintf("addrof");
	break;
	case FinCTokenType_Valueof:
	kprintf("valueof");
	break;
	case FinCTokenType_Identifier:
	kprintf("id");
	break;
	case FinCTokenType_Eof:
	kprintf("eof");
	break;
	case FinCTokenType_Bad:
	kprintf("bad");
	break;
	}
}

#endif
