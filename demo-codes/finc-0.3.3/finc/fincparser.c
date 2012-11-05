#include <stdio.h>

#include <finc/fincparser.h>
#include <finc/finclang.h>
#include <finc/finctype.h>
#include <finc/finccontext.h>

#ifdef USING_FILE
static unsigned char* file_input(const char *arg);
#endif
static unsigned char* buffer_input(const char *arg);

#ifdef USING_FILE
static void parser_internal(FinCParser* self);
#endif
static void parser_internal_line(FinCParser* self);
static FinCNode* proc_func_variable_decl(FinCParser* self);
static FinCNode* proc_variable_decl(FinCParser* self);
static FinCNode* proc_package(FinCParser* self);
static FinCNode* proc_package_func(FinCParser* self);
static FinCNode* proc_struct(FinCParser* self);
static FinCNode* proc_field_list(FinCParser* self);
static FinCNode* proc_field(FinCParser* self);
#ifdef USING_FILE
static FinCNode* proc_import(FinCParser* self);
#endif
static FinCNode* proc_param_list(FinCParser* self);
static FinCNode* proc_type(FinCParser* self);
static FinCNode* proc_identifier(FinCParser* self);
static FinCNode* proc_expr(FinCParser* self);
static FinCNode* proc_assign_expr(FinCParser* self);
static FinCNode* proc_condition_expr(FinCParser* self);
static FinCNode* proc_logical_or_expr(FinCParser* self);
static FinCNode* proc_logical_and_expr(FinCParser* self);
static FinCNode* proc_inclusive_or_expr(FinCParser* self);
static FinCNode* proc_exclusive_or_expr(FinCParser* self);
static FinCNode* proc_and_expr(FinCParser* self);
static FinCNode* proc_equality_expr(FinCParser* self);
static FinCNode* proc_relational_expr(FinCParser* self);
static FinCNode* proc_shift_expr(FinCParser* self);
static FinCNode* proc_additive_expr(FinCParser* self);
static FinCNode* proc_multiplicative_expr(FinCParser* self);
static FinCNode* proc_cast_expr(FinCParser* self);
static FinCNode* proc_unary_expr(FinCParser* self);
static FinCNode* proc_postfix_expr(FinCParser* self);
static FinCNode* proc_primary_expr(FinCParser* self);
static FinCNode* proc_call_param_list(FinCParser* self);
static FinCNode* proc_statement(FinCParser* self);
static FinCNode* proc_in_block_statement(FinCParser* self);
static FinCNode* proc_block_statement(FinCParser* self);
static FinCNode* proc_expr_statement(FinCParser* self);
static FinCNode* proc_for_statement(FinCParser* self);
static FinCNode* proc_while_statement(FinCParser* self);
static FinCNode* proc_if_statement(FinCParser* self);
static FinCNode* proc_simple_statement(FinCParser* self);
static void make_pkg_begin(FinCParser* self, unsigned char* p_package);
static void make_pkg_func_begin (FinCParser* self, FinCNode* p_type, FinCNode* p_identifier);
static FinCNode* make_pkg_func_finish (FinCParser* self);
static FinCNode* make_pkg_finish(FinCParser* self);
static void make_func_begin (FinCParser* self, FinCNode* p_type, FinCNode* p_identifier);
static void make_func_add_param (FinCParser* self, FinCNode* p_type, FinCNode* p_name);
static void make_func_opt_param (FinCParser* self);
static FinCNode* make_func_finish (FinCParser* self, FinCNode* p_code);
static void make_block_begin (FinCParser* self);
static void make_block_add (FinCParser* self, FinCNode* p_node);
static FinCNode* make_block_finish (FinCParser* self);
static void make_call_begin (FinCParser* self, unsigned char* p_identifier);
static void make_call_add (FinCParser* self, FinCNode* p_node);
static FinCNode* make_call_finish (FinCParser* self);

static FinCNode* make_efunc  (unsigned char* p_func);
static FinCNode* make_efunc1 (unsigned char* p_func, FinCNode* p_node1);
static FinCNode* make_efunc2 (unsigned char* p_func, FinCNode* p_node1, FinCNode* p_node2);
static FinCNode* make_efunc3 (unsigned char* p_func, FinCNode* p_node1, FinCNode* p_node2, FinCNode* p_node3);
static FinCNode* make_efunc4 (unsigned char* p_func, FinCNode* p_node1, FinCNode* p_node2, FinCNode* p_node3, FinCNode* p_node4);

#define check_token(token, lex, type) if ( (token) != (type) ) \
	{ \
		finc_lang_error_line(lex, "Parser Error: Invalid token."); \
		finc_context_error_inc(g_finc_context); \
		finc_token_replay(lex); \
	}

#ifdef USING_DOUBLE
#define is_double(token) ((token) == FinCTokenType_Type_Double)
#else
#define is_double(token) 0
#endif
#ifdef USING_FLOAT
#define is_float(token) ((token) == FinCTokenType_Type_Float)
#else
#define is_float(token) 0
#endif

#define is_base_type(token)	(token) == FinCTokenType_Type_Void || (token) == FinCTokenType_Type_Char \
	|| (token) == FinCTokenType_Type_Short || (token) == FinCTokenType_Type_Int \
	|| is_double(token) \
	|| is_float(token) \
	|| (token) == FinCTokenType_Type_Pointer || (token) == FinCTokenType_Type_String

#define is_type(token) (token) == FinCTokenType_Identifier || is_base_type(token)

#define next_token(token, lex)	(token) = finc_token_token(lex)

#define match_token(token, lex, type)	next_token(token, lex); \
	check_token(token, lex, type)

FinCParser* finc_parser_new()
{
	FinCParser* self;

	self = (FinCParser*)mem_new(sizeof(FinCParser));

	self->tree_root = NULL;
	self->lex = NULL;
	self->parse_string = NULL;
	self->lang_env = NULL;

	self->stack_call = stack_new();
	self->stack_block = stack_new();

	self->current_func = NULL;
	self->current_block = NULL;
	self->current_call = NULL;
	self->current_type = NULL;
	self->current_pkg = NULL;
	self->current_struct= NULL;
	
	object_init_object((Object*)self, finc_parser_destroy);

	return self;
}

void finc_parser_destroy(Object* self)
{
	unref( ((FinCParser*)self)->tree_root );
	unref( ((FinCParser*)self)->lex );
	unref( ((FinCParser*)self)->parse_string );

	unref( ((FinCParser*)self)->lang_env );

	unref( ((FinCParser*)self)->stack_call);
	unref( ((FinCParser*)self)->stack_block);

	unref( ((FinCParser*)self)->current_func);
	unref( ((FinCParser*)self)->current_block);
	unref( ((FinCParser*)self)->current_call);
	unref( ((FinCParser*)self)->current_type);
	unref( ((FinCParser*)self)->current_pkg);
	unref( ((FinCParser*)self)->current_struct);

	mem_destroy(self);
}

void finc_parser_set_env (FinCParser* self, FinCLangEnv* env)
{
	unref(self->lang_env);
	self->lang_env = addref(FinCLangEnv, env);
}

static int parse_string_pos;
static unsigned char* buffer_input(const char *arg)
{
	static char line[512];
	char* p, ch;
	String* buffer = (String*)arg;
	line[0] = '\0';

	p = line;
	
	if (string_at(buffer, parse_string_pos)=='\0') return NULL;

	while( ((ch = string_at(buffer, parse_string_pos++)) != '\0') && (ch != '\n') ) *p++ = ch;
	if ( string_at(buffer, parse_string_pos -1) == '\0') parse_string_pos --;

	*p++ = ch;
	*p = '\0';

	return line;
}

void finc_parser_parser_string(FinCParser* self, String* str)
{
	self->parse_string = addref(String, str);

	self->lex = finc_token_new();
	self->lex->arg = (char*)self->parse_string;
	self->lex->read_line = buffer_input;
	parse_string_pos = 0;

	parser_internal_line(self);
	unref(self->lex);
	self->lex = NULL;
	unref(str);
}

#ifdef USING_FILE
static unsigned char* file_input(const char *arg)
{
	static char line[512];
	line[0] = 0;

	return fgets(line, sizeof line, (FILE *)arg);
}

void finc_parser_parser_file(FinCParser* self, const char* filename)
{
	FILE* fp;

	fp = fopen(filename, "r");
	if ( fp == NULL )
	{
		printf("Can't open input file.\n");
		return;
	}

	self->lex = finc_token_new();
	self->lex->arg = (char*)fp;
	self->lex->read_line = file_input;

	parser_internal(self);

	fclose(fp);
	unref(self->lex);
	self->lex = NULL;
}
#endif

/**
line_input -> empty
	| line_input line_start

line_start -> decl_import
	| decl_global
	| decl_function
	| decl_struct
	| decl_package
	| statement_block
	| statement_expr
	| statement_for
	| statement_while
	| statement_if
*/
static void parser_internal_line(FinCParser* self)
{
	FinCNode* node;
	FinCTokenType token;
	String* str;

	self->tree_root = finc_node_new();
	finc_node_set_block (self->tree_root);

	next_token(token, self->lex);
	while ( (token != FinCTokenType_Eof) && (token != FinCTokenType_Bad) )
	{
		switch ( token )
		{
#ifdef USING_FILE		
		case FinCTokenType_Import:
			finc_token_replay(self->lex);
			proc_import(self);
			break;
#endif			
		case FinCTokenType_Struct:
			finc_token_replay(self->lex);
			proc_struct(self);
			break;
		case FinCTokenType_Package:
			finc_token_replay(self->lex);
			proc_package(self);
			break;
		case FinCTokenType_Left_Curly:
			finc_token_replay(self->lex);
			node = proc_block_statement(self);
			if (node)
			{
				finc_node_add( self->tree_root, node);
				unref(node);
			}
			break;
		case FinCTokenType_For:
			finc_token_replay(self->lex);
			node = proc_for_statement(self);
			if (node)
			{
				finc_node_add( self->tree_root, node);
				unref(node);
			}
			break;
		case FinCTokenType_While:
			finc_token_replay(self->lex);
			node = proc_while_statement(self);
			if (node)
			{
				finc_node_add( self->tree_root, node);
				unref(node);
			}
			break;
		case FinCTokenType_If:
			finc_token_replay(self->lex);
			node = proc_if_statement(self);
			if (node)
			{
				finc_node_add( self->tree_root, node);
				unref(node);
			}
			break;
		default:
			if ( is_base_type(token) ) /*function or variable declaration*/
			{
				finc_token_replay(self->lex);
				node = proc_func_variable_decl(self);
			}
			else if ( token == FinCTokenType_Identifier )
			{
				str = finc_token_get_token(self->lex);
				if (finc_lang_check_type(self->lang_env, str))/*it's a struct type.*/
				{
					unref(str);
					finc_token_replay(self->lex);
					node = proc_func_variable_decl(self);
				}
				else
				{
					unref(str);
					finc_token_replay(self->lex);
					node = proc_expr_statement(self);
				}
			}
			else /*statement_expr*/
			{
				finc_token_replay(self->lex);
				node = proc_expr_statement(self);
			}

			if (node)
			{
				finc_node_add( self->tree_root, node);
				unref(node);
			}
			break;
		}
		next_token(token, self->lex);
	}
	/*end of line parser*/
}

/**
input -> empty
	| input declaration

declaration -> decl_import
	| decl_global
	| decl_function
	| decl_struct
	| decl_package
*/
#ifdef USING_FILE
static void parser_internal(FinCParser* self)
{
	FinCNode* node;
	FinCTokenType token;

	self->tree_root = finc_node_new();
	finc_node_set_block (self->tree_root);

	next_token(token, self->lex);
	while ( token == FinCTokenType_Package
		|| token == FinCTokenType_Struct
		|| token == FinCTokenType_Import
		|| is_type(token) )
	{
		switch ( token )
		{
		case FinCTokenType_Import:
			finc_token_replay(self->lex);
			proc_import(self);
			break;
		case FinCTokenType_Struct:
			finc_token_replay(self->lex);
			proc_struct(self);
			break;
		case FinCTokenType_Package:
			finc_token_replay(self->lex);
			proc_package(self);
			break;
		default:
			if ( is_type(token) )
			{
			    finc_token_replay(self->lex);
			    node = proc_func_variable_decl(self);
			    if (node)
			    {
				finc_node_add( self->tree_root, node);
				unref(node);
			    }
			}
			else
			{
			    finc_lang_error_line(self->lex, "Parser Error: expecting a declaration.");
			    finc_context_error_inc(g_finc_context);
			}
			break;
		}
		next_token(token, self->lex);
	}

	if ( token != FinCTokenType_Eof )
	{
		finc_lang_error_line(self->lex, "Parser Error:expecting a EOF.\n");
		finc_context_error_inc(g_finc_context);
	}
	/*end of main parser*/
}
#endif

/*
process for function and variable declaration.
decl_variable -> type declaration_list ';'
	| type identifier '[' V_INT ']' ';'
	| type identifier '[' ']' ';'
declarator_list -> declarator_list ',' declarator
	| declarator
declarator -> identifier
	| identifier ASSIGN expr_assign

decl_function -> type identifier '(' decl_param_type_list ')' statement_block
*/
static FinCNode* proc_func_variable_decl(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* type;
	FinCNode* id;
	FinCNode* statement;
	FinCNode* assign;
	FinCNode* node_func;
	Bool b_static, b_unsigned;

	b_static = FALSE;
	b_unsigned = FALSE;

	type = proc_type(self);
	id = proc_identifier(self);/*process id.*/

	next_token(token, self->lex);
	switch ( token )
	{
	case FinCTokenType_Left_Brace:/*'[', it's a array variable declaration.*/
		next_token(token, self->lex);
		if (token == FinCTokenType_Right_Brace)/*it's a dynamic array declaration.*/
		{
			type->type->array_type = FinCArrayType_Dynamic;
			type->type->array_size = 0;

			match_token(token, self->lex, FinCTokenType_Semicolon);
			finc_node_add(type, id);
			unref(id);
			return make_efunc1("global", type);
		}
		else if (token == FinCTokenType_Int)/*it's a fixed array declaration.*/
		{
			type->type->array_type = FinCArrayType_Fixed;
			type->type->array_size = (int)self->lex->last_double;

			match_token(token, self->lex, FinCTokenType_Right_Brace);
			match_token(token, self->lex, FinCTokenType_Semicolon);
			finc_node_add(type, id);
			unref(id);
			return make_efunc1("global", type);
		}
		else
		{
			finc_lang_error_line(self->lex, "Parser Error:expecting an interger in an array declaration.");
			finc_context_error_inc(g_finc_context);
			finc_token_replay(self->lex);
			return NULL;
		}
		break;

	case FinCTokenType_Comma:/*',', it's a variable_list declaration.*/
		finc_node_add(type, id);
		unref(id);

		id = proc_identifier(self);

		next_token(token, self->lex);
		if ( token == FinCTokenType_Assign )
		{
			assign = proc_assign_expr(self);
			finc_node_add (id, assign);
			unref(assign);

			next_token(token, self->lex);
		}
		finc_node_add(type, id);
		unref(id);

		while ( token == FinCTokenType_Comma )
		{
			id = proc_identifier(self);

			next_token(token, self->lex);
			if ( token == FinCTokenType_Assign )
			{
				assign = proc_assign_expr(self);
				finc_node_add (id, assign);
				unref(assign);
				next_token(token, self->lex);
			}
			finc_node_add(type, id);
			unref(id);
		}

		check_token(token, self->lex, FinCTokenType_Semicolon);
		return make_efunc1("global", type);
		break;

	case FinCTokenType_Assign:/*'=', it's a variable with assign declaration.*/
		assign = proc_assign_expr(self);

		finc_node_add (id, assign);
		unref(assign);
		finc_node_add (type, id);
		unref(id);

		next_token(token, self->lex);
		while ( token == FinCTokenType_Comma )
		{
			id = proc_identifier(self);

			next_token(token, self->lex);
			if ( token == FinCTokenType_Assign )
			{
				assign = proc_assign_expr(self);
				finc_node_add (id, assign);
				unref(assign);
				next_token(token, self->lex);
			}
			finc_node_add(type, id);
			unref(id);
		}

		check_token(token, self->lex, FinCTokenType_Semicolon);
		return make_efunc1("global", type);

	case FinCTokenType_Semicolon:/*';', it's a variable declaration.*/
		finc_node_add(type, id);
		unref(id);

		return make_efunc1("global", type);

	case FinCTokenType_Left_Paren:/*'(', it's a function declaration.*/
		make_func_begin(self, type, id);

		next_token(token, self->lex);
		if ( token != FinCTokenType_Right_Paren )
		{
			finc_token_replay(self->lex);
			proc_param_list(self);
			match_token(token, self->lex, FinCTokenType_Right_Paren);
		}

		statement = proc_block_statement(self);
		node_func = make_func_finish(self, statement);
		finc_lang_proc_func(self->lang_env, node_func);
		unref(node_func);
		return NULL;
		break;

	default:
		finc_lang_error_line(self->lex, "Parser Error:variable or function declaration error.");
		finc_context_error_inc(g_finc_context);
		unref(type);
		unref(id);
		return NULL;
		break;
	}
}

/*
process for function and variable declaration.
decl_variable -> type declaration_list ';'
	| type identifier '[' V_INT ']'
	| type identifier '[' ']'
declarator_list -> declarator_list ',' declarator
	| declarator
declarator -> identifier
	| identifier ASSIGN expr_assign
*/
static FinCNode* proc_variable_decl(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* type;
	FinCNode* id;
	FinCNode* assign;
	Bool b_static, b_unsigned;

	b_static = FALSE;
	b_unsigned = FALSE;

	type = proc_type(self);
	id = proc_identifier(self);/*process id.*/

	next_token(token, self->lex);
	switch ( token )
	{
	case FinCTokenType_Left_Brace:/*'[', it's a array variable declaration.*/
		next_token(token, self->lex);
		if (token == FinCTokenType_Right_Brace)/*it's a dynamic array declaration.*/
		{
			type->type->array_type = FinCArrayType_Dynamic;
			type->type->array_size = 0;

			match_token(token, self->lex, FinCTokenType_Semicolon);
			finc_node_add(type, id);
			unref(id);
			return type;
		}
		else if (token == FinCTokenType_Int)/*it's a fixed array declaration.*/
		{
			type->type->array_type = FinCArrayType_Fixed;
			type->type->array_size = (int)self->lex->last_double;

			match_token(token, self->lex, FinCTokenType_Right_Brace);
			match_token(token, self->lex, FinCTokenType_Semicolon);
			finc_node_add(type, id);
			unref(id);
			return type;
		}
		else
		{
			finc_lang_error_line(self->lex, "Parser Error:must use a interger in an array declaration.");
			finc_context_error_inc(g_finc_context);
			return NULL;
		}
		break;

	case FinCTokenType_Comma:/*',', it's a variable_list declaration.*/
		finc_node_add(type, id);
		unref(id);

		id = proc_identifier(self);

		next_token(token, self->lex);
		if ( token == FinCTokenType_Assign )
		{
			assign = proc_assign_expr(self);
			finc_node_add (id, assign);
			unref(assign);

			next_token(token, self->lex);
		}
		finc_node_add(type, id);
		unref(id);

		while ( token == FinCTokenType_Comma )
		{
			id = proc_identifier(self);

			next_token(token, self->lex);
			if ( token == FinCTokenType_Assign )
			{
				assign = proc_assign_expr(self);
				finc_node_add (id, assign);
				unref(assign);
				next_token(token, self->lex);
			}
			finc_node_add(type, id);
			unref(id);
		}

		check_token(token, self->lex, FinCTokenType_Semicolon);
		return type;
		break;

	case FinCTokenType_Assign:/*'=', it's a variable with assign declaration.*/
		assign = proc_assign_expr(self);

		finc_node_add (id, assign);
		unref(assign);
		finc_node_add (type, id);
		unref(id);

		next_token(token, self->lex);
		while ( token == FinCTokenType_Comma )
		{
			id = proc_identifier(self);

			next_token(token, self->lex);
			if ( token == FinCTokenType_Assign )
			{
				assign = proc_assign_expr(self);
				finc_node_add (id, assign);
				unref(assign);
				next_token(token, self->lex);
			}
			finc_node_add(type, id);
			unref(id);
		}

		check_token(token, self->lex, FinCTokenType_Semicolon);
		return type;
		break;

	case FinCTokenType_Semicolon:/*';', it's a variable declaration.*/
		finc_node_add(type, id);
		unref(id);
		return type;
		break;

	default:
		finc_lang_error_line(self->lex, "Parser Error:variable declaration error.");
		finc_context_error_inc(g_finc_context);
		unref(type);
		unref(id);
		return NULL;
		break;
	}
}

/*
decl_package -> PACKAGE V_STRING '{' decl_package_func_list '}' ';'
*/
static FinCNode* proc_package(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* pkg;

	match_token(token, self->lex, FinCTokenType_Package);
	match_token(token, self->lex, FinCTokenType_String);
	make_pkg_begin(self, string_get_str(self->lex->last_str));

	match_token(token, self->lex, FinCTokenType_Left_Curly);
	next_token(token, self->lex);
	if (token != FinCTokenType_Right_Curly)
	{
		finc_token_replay(self->lex);
		proc_package_func(self);
		match_token(token, self->lex, FinCTokenType_Right_Curly);
	}

	match_token(token, self->lex, FinCTokenType_Semicolon);
	pkg = make_pkg_finish(self);
	
#ifdef USING_PACKAGE
	finc_lang_proc_pkg(self->lang_env, pkg);
#endif
	unref(pkg);

	return NULL;
}

/*
decl_package_func_list -> decl_package_func
	| decl_package_func_list decl_package_func
decl_package_func -> type identifier '(' decl_param_type_list ')' ';'
*/
static FinCNode* proc_package_func(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* type;
	FinCNode* id;
	FinCNode* node_pkg;

	next_token(token, self->lex);
	while ( is_type(token) )
	{
		finc_token_replay(self->lex);
		type = proc_type(self);
		id = proc_identifier(self);
		
		make_pkg_func_begin(self, type, id);
		match_token(token, self->lex, FinCTokenType_Left_Paren);
		next_token(token, self->lex);
		if ( token != FinCTokenType_Right_Paren )
		{
			finc_token_replay(self->lex);
			proc_param_list(self);

			match_token(token, self->lex, FinCTokenType_Right_Paren);
		}
		match_token(token, self->lex, FinCTokenType_Semicolon);
		node_pkg = make_pkg_func_finish(self);
		finc_node_add (self->current_pkg, node_pkg);
		unref(node_pkg);

		next_token(token, self->lex);
	}
	finc_token_replay(self->lex);

	return NULL;/*support for pkg.*/
}

/*
decl_struct -> STRUCT identifier '{' decl_field_list '}' ';'
*/
static FinCNode* proc_struct(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* id;
	FinCNode* node_struct;

	match_token(token, self->lex, FinCTokenType_Struct);

	id = proc_identifier(self);
	if (id) 
	{
		self->current_struct = finc_node_new_func ("struct");
		finc_node_add (self->current_struct, id);
		unref (id);
	}
	else return NULL;

	match_token(token, self->lex, FinCTokenType_Left_Curly);
	next_token(token, self->lex);

	if ( token != FinCTokenType_Right_Curly )
	{
		finc_token_replay(self->lex);
		proc_field_list(self);
	}

	match_token(token, self->lex, FinCTokenType_Right_Curly);
	match_token(token, self->lex, FinCTokenType_Semicolon);
	node_struct = self->current_struct;
	self->current_struct = NULL;

	finc_lang_proc_struct(self->lang_env, node_struct);
	unref(node_struct);
	return NULL;
}

/*
decl_field_list -> decl_field_declarator
	| decl_field_list decl_field_declarator
*/
static FinCNode* proc_field_list(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* field;

	next_token(token, self->lex);
	while ( (token!= FinCTokenType_Right_Curly) && (is_type(token)) )
	{
		finc_token_replay(self->lex);
		field = proc_field(self);
		finc_node_add (self->current_struct, field);
		unref(field);
		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return NULL;
}

/*
decl_field_declarator -> type struct_declarator_list ';'
	| type identifier '[' V_INT ']'
	| type identifier '[' ']'
struct_declarator_list -> struct_declarator_list ',' struct_declarator
	| struct_declarator
struct_declarator -> identifier
*/
static FinCNode* proc_field(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* type;
	FinCNode* id;
	FinCNode* assign;
	Bool b_static, b_unsigned;

	b_static = FALSE;
	b_unsigned = FALSE;

	type = proc_type(self);
	id = proc_identifier(self); /* process id. */

	next_token(token, self->lex);
	switch ( token )
	{
	case FinCTokenType_Left_Brace:/*'[', it's a array variable declaration.*/
		next_token(token, self->lex);
		if (token == FinCTokenType_Right_Brace)/*it's a dynamic array declaration.*/
		{
			type->type->array_type = FinCArrayType_Dynamic;
			type->type->array_size = 0;

			match_token(token, self->lex, FinCTokenType_Semicolon);
			finc_node_add(type, id);
			unref(id);
			return type;
		}
		else if (token == FinCTokenType_Int)/*it's a fixed array declaration.*/
		{
			type->type->array_type = FinCArrayType_Fixed;
			type->type->array_size = self->lex->last_long;

			match_token(token, self->lex, FinCTokenType_Right_Brace);
			match_token(token, self->lex, FinCTokenType_Semicolon);
			finc_node_add(type, id);
			unref(id);
			return type;
		}
		else
		{
			finc_lang_error_line(self->lex, "Parser Error:must use a interger in an array declaration.");
			finc_context_error_inc(g_finc_context);
			return NULL;
		}
		break;

	case FinCTokenType_Comma:/*',', it's a variable_list declaration.*/
		finc_node_add(type, id);
		unref(id);

		id = proc_identifier(self);

		next_token(token, self->lex);
		if ( token == FinCTokenType_Assign )
		{
			assign = proc_assign_expr(self);
			finc_node_add (id, assign);
			unref(assign);

			next_token(token, self->lex);
		}
		finc_node_add(type, id);
		unref(id);

		while ( token == FinCTokenType_Comma )
		{
			id = proc_identifier(self);

			next_token(token, self->lex);
			if ( token == FinCTokenType_Assign )
			{
				assign = proc_assign_expr(self);
				finc_node_add (id, assign);
				unref(assign);
				next_token(token, self->lex);
			}
			finc_node_add(type, id);
			unref(id);
		}

		check_token(token, self->lex, FinCTokenType_Semicolon);
		return type;
		break;

	case FinCTokenType_Semicolon:/*';', it's a variable declaration.*/
		finc_node_add(type, id);
		unref(id);
		return type;
		break;

	default:
		finc_lang_error_line(self->lex, "Parser Error:variable declaration error.");
		finc_context_error_inc(g_finc_context);
		unref(type);
		unref(id);
		return NULL;
		break;
	}
}

#ifdef USING_FILE
/**
decl_import -> IMPORT V_STRING ';'
*/
static FinCNode* proc_import(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* string;
	FinCNode* import;

	match_token(token, self->lex, FinCTokenType_Import);
	match_token(token, self->lex, FinCTokenType_String);

	/*perform at last.*/
	string = finc_node_new_string(string_get_str(self->lex->last_str));
	match_token(token, self->lex, FinCTokenType_Semicolon);

	import = make_efunc1 ("import", string);

	finc_lang_proc_import(self->lang_env, import);
	unref(import);

	return NULL;
}
#endif

/**
decl_param_type_list -> decl_param_list
	| decl_param_list ',' OPT_PARAM
decl_param_list -> empty
	| decl_param
	| decl_param_list ',' decl_param
decl_param -> type identifier
	| type identifier '[' ']'
	| type identifier '[' V_INT ']'
*/
static FinCNode* proc_param_list(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* type;
	FinCNode* id;

	type = proc_type(self);
	id = proc_identifier(self);

	next_token(token, self->lex);
	if (token == FinCTokenType_Left_Brace)/*if it's a array param.*/
	{
		next_token(token, self->lex);
		if (token == FinCTokenType_Right_Brace)
		{
			type->type->array_type = FinCArrayType_Dynamic;
			type->type->array_size = 0;
		}
		else
		{
			type->type->array_type = FinCArrayType_Fixed;
			type->type->array_size = (int)self->lex->last_double;
		}

		next_token(token, self->lex);
	}
	make_func_add_param(self, type, id);

	while (token == FinCTokenType_Comma)
	{
		type = proc_type(self);
		id = proc_identifier(self);

		next_token(token, self->lex);
		if (token == FinCTokenType_Left_Brace)/*if it's a array param.*/
		{
			next_token(token, self->lex);
			if (token == FinCTokenType_Right_Brace)
			{
				type->type->array_type = FinCArrayType_Dynamic;
				type->type->array_size = 0;
			}
			else
			{
				type->type->array_type = FinCArrayType_Fixed;
				type->type->array_size = (int)self->lex->last_double;
			}

			next_token(token, self->lex);
		}
		make_func_add_param(self, type, id);
	}

	finc_token_replay(self->lex);
	return NULL;
}

#ifdef USING_OO
/*
decl_class -> CLASS identifier [:] [public] [class] class_scope '{' decl_class_member_list '}' [;]
*/
static FinCNode* proc_class(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* id;

	match_token(token, self->lex, FinCTokenType_Class);

	id = proc_identifier(self);
	if ( id )
	{
	}
	else return NULL;

	next_token(token, self->lex);
	if ( token != FinCTokenType_Colon ) /* [:] */
	{
		match_token(token, self->lex, FinCTokenType_Left_Curly); /* { */
		next_token (token, self->lex);
		
		if ( token != FinCTokenType_Right_Curly ) /* } */
		{
			finc_token_replay(self->lex);
			proc_class_member_list(self); /* decl_class_member_list */
		}
		
		match_token(token, self->lex, FinCTokenType_Right_Curly);
		match_token(token, self->lex, FinCTokenType_Semicolon); /* ; */
	}
	else
	{
		next_token(token, self->lex);
		if ( token != FinCTokenType_Public ) finc_token_replay(self->lex);
		next_token(token, self->lex);
		if ( token != FinCTokenType_Class  ) finc_token_replay(self->lex);
		proc_class_scope(self);
	}
}

/*
class_scope -> ID
	| class_scope ':'':' ID
*/
static FinCNode* proc_class_scope(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* id;

	id = proc_identifier(self); /* ID */
	while ( token == FinCTokenType_Identifier )
	{
		id = proc_identifier(self);
	}

	return id;
}

/*
decl_class_member_list -> decl_class_class_member
	| decl_class_member_list decl_class_member
*/
static FinCNode* proc_class_member_list(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* field;

	next_token(token, self->lex);
	while ( (token!= FinCTokenType_Right_Curly) && ((is_type(token))||
		token == FinCTokenType_Public	||
		token == FinCTokenType_Private	||
		token == FinCTokenType_Virtual	||
		token == FinCTokenType_Class	|| ) )
	{
		finc_token_replay(self->lex);
		member = proc_class_member(self);
		finc_node_add(self->current_class, member);
		unref(member);
		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return NULL;
}

/*
decl_member -> access-specifier decl_variable
	| access-specifier type identifier '(' decl_param_type_list ')' statement_block
	| virtual access-specifier type identifier '(' decl_param_type_list ')' statement_block
	| virtual access-specifier type identifier '(' decl_param_type_list ')' '=' '0' ';'
	| access-specifier decl_class
access-specifier -> PUBLIC | PRIVATE
*/
static FinCNode* proc_class_member(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* _class;
	FinCNode* type;
	FinCNode* id;
	FinCNode* assign;
	Bool b_public, b_virtual, b_static, b_unsigned;

	b_public	= FALSE;
	b_virtual	= FALSE;
	b_static	= FALSE;
	b_unsigned	= FALSE;

	next_token(token, self->lex);
	if ( token == FinCTokenType_Virtual ) b_virtual = TRUE;
	else if ( token == FinCTokenType_Public ) b_public = TRUE;
	else if ( token == FinCTokenType_Private ) b_public = FALSE;
	else if ( token == FinCTokenType_Static ) b_static = TRUE;
	else if ( token == FinCTokenType_unsigned ) b_unsigned = TRUE;
	else if ( token == FinCTokenType_Class )
	{
		finc_token_replay(self->lex);
		_class = proc_class(self);
	}
	else finc_token_replay(self->lex);

	/* attribute and method */
}

#endif

/*
type -> type_list
	| identifier
type_list -> type_basic
	| type_list type_basic
type_basic -> VOID
	| CHAR
	| SHORT
	| INT
	| STRING
	| POINTER
	| FLOAT
	| DOUBLE
	| BOOL

identifier -> IDENTIFIER

note:
there is only one base type in type_list.
so there are only four case:
id
base_type
unsigned base_type
statice [unsigned] base_type
*/
static FinCNode* proc_type(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* type;
	String* str;

	type = NULL;
	next_token(token, self->lex);
	if ( token == FinCTokenType_Identifier ) /*case 1, id*/
	{
		str = finc_token_get_token(self->lex);
		if (finc_lang_check_type(self->lang_env, str))/*it's a struct type.*/
		{
			type = finc_node_new_type(str, FinCArrayType_None, 0);
			unref(str);
		}
		else
		{
			finc_token_replay(self->lex);
			finc_lang_error_line(self->lex, "Parser Error:unknow struct name.");
			unref(str);
			return NULL;
		}
	}
	else if ( is_base_type(token) ) /*case 2, base_type*/
	{
		str = finc_token_get_token(self->lex);
		type = finc_node_new_type(str, FinCArrayType_None, 0);
		unref(str);
	}
	else if ( token == FinCTokenType_Unsigned ) /*case 3, unsigned base_type*/
	{
		next_token(token, self->lex);
		if ( is_base_type(token) )
		{
			str = finc_token_get_token(self->lex);
			type = finc_node_new_type(str, FinCArrayType_None, 0);
			unref(str);
		}
		else
		{
			finc_token_replay(self->lex);
			finc_lang_error_line(self->lex, "Parser Error:expecting a declaration type.");
			return NULL;
		}
	}
	else if ( token == FinCTokenType_Static ) /*case 4, static [unsigned] base_type*/
	{
		next_token(token, self->lex);
		if ( token == FinCTokenType_Unsigned )
		{
			next_token(token, self->lex);
			if ( is_base_type(token) )
			{
				str = finc_token_get_token(self->lex);
				type = finc_node_new_type(str, FinCArrayType_None, 0);
				unref(str);
			}
			else
			{
				finc_lang_error_line(self->lex, "Parser Error:expecting a declaration type.");
			}
		}
		else if ( is_base_type(token) )
		{
			str = finc_token_get_token(self->lex);
			type = finc_node_new_type( str, FinCArrayType_None, 0);
			unref(str);
		}
		else
		{
			finc_token_replay(self->lex);
			finc_lang_error_line(self->lex, "Parser Error:expecting a declaration type.");
			return NULL;
		}
	}
	else
	{
		finc_token_replay(self->lex);
		finc_lang_error_line(self->lex, "Parser Error:unknow type.");
		return NULL;
	}

	return type;
}

/*
identifier:
  IDENTIFIER
*/
static FinCNode* proc_identifier(FinCParser* self)
{
	FinCTokenType token;

	match_token(token, self->lex, FinCTokenType_Identifier);
	return finc_node_new_name(string_get_str(self->lex->last_str));
}

/**
expr -> expr_assign
	| expr ',' expr_assign
*/
static FinCNode* proc_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* assign;
	FinCNode* assign_new;

	assign = proc_assign_expr(self);

	next_token(token, self->lex);
	while ( token == FinCTokenType_Comma )
	{
		assign_new = proc_assign_expr(self);
		assign = make_efunc2(",", assign, assign_new);

		next_token(token, self->lex);
	}
	finc_token_replay(self->lex);

	return assign;
}

/**
expr_assign -> expr_condition
	| expr_unary ASSIGN expr_assign
*/
static FinCNode* proc_assign_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* cond;
	FinCNode* assign;

	cond = proc_condition_expr(self);

	next_token(token, self->lex);

	if ( token == FinCTokenType_Assign )
	{
		assign = proc_assign_expr(self);
		return make_efunc2("=", cond, assign);
	}
	else finc_token_replay(self->lex);

	return cond;
}

/**
expr_condition -> expr_logic_or
	| expr_logic_or '?' expr ':' expr_condition
*/
static FinCNode* proc_condition_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* logic_or;
	FinCNode* expr;
	FinCNode* cond_expr;

	logic_or = proc_logical_or_expr(self);

	next_token(token, self->lex);
	if (token == FinCTokenType_Question)
	{
		expr = proc_expr(self);

		match_token(token, self->lex, FinCTokenType_Colon);

		cond_expr = proc_condition_expr(self);
		return make_efunc3("?", logic_or, expr, cond_expr);
	}

	finc_token_replay(self->lex);
	return logic_or;
}

/**
expr_logic_or -> expr_logic_and
	| expr_logic_or OR expr_logic_and
*/
static FinCNode* proc_logical_or_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* logic_and;
	FinCNode* logic_and_new;

	logic_and = proc_logical_and_expr(self);

	next_token(token, self->lex);
	while ( token == FinCTokenType_Logic_Or)
	{
		logic_and_new = proc_logical_and_expr(self);
		logic_and = make_efunc2("&&", logic_and, logic_and_new);

		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return logic_and;
}

/*
expr_logic_and -> expr_inclusive_or
	| expr_logic_and AND expr_inclusive_or
*/
static FinCNode* proc_logical_and_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* or;
	FinCNode* or_new;
	
	or = proc_inclusive_or_expr(self);
	next_token(token, self->lex);
	while ( token == FinCTokenType_Logic_And )
	{
		or_new = proc_inclusive_or_expr(self);
		or = make_efunc2("&&", or, or_new);

		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return or;
}

/*
expr_inclusive_or -> expr_exclusive_or
	| expr_inclusive_or '|' expr_exclusive_or
*/
static FinCNode* proc_inclusive_or_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* xor;
	FinCNode* xor_new;
	
	xor = proc_exclusive_or_expr(self);
	next_token(token, self->lex);
	while ( token == FinCTokenType_Or )
	{
		xor_new = proc_exclusive_or_expr(self);
		xor = make_efunc2("|", xor, xor_new);

		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return xor;
}

/*
expr_exclusive_or -> expr_and
	| expr_exclusive '^' expr_and
*/
static FinCNode* proc_exclusive_or_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* and;
	FinCNode* and_new;
	
	and = proc_and_expr(self);
	next_token(token, self->lex);
	while ( token == FinCTokenType_XOR )
	{
		and_new = proc_and_expr(self);
		and = make_efunc2("^", and, and_new);

		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return and;
}

/*
expr_and -> expr_equality
	| expr_and '&' expr_equality
*/
static FinCNode* proc_and_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* equality;
	FinCNode* equality_new;
	
	equality = proc_equality_expr(self);
	next_token(token, self->lex);
	while ( token == FinCTokenType_And )
	{
		equality_new = proc_equality_expr(self);
		equality = make_efunc2("&", equality, equality_new);

		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return equality;
}

/*
expr_equality -> expr_relational
	| expr_equality EQ expr_relational
	| expr_equality NE expr_relational
*/
static FinCNode* proc_equality_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* rel;
	FinCNode* rel_new;

	rel = proc_relational_expr(self);
	next_token(token, self->lex);
	while ( token == FinCTokenType_Eq || token == FinCTokenType_Not_Eqs)
	{
		rel_new = proc_relational_expr(self);
		switch (token)
		{
		case FinCTokenType_Eq:
			rel = make_efunc2("==", rel, rel_new);
			break;
		case FinCTokenType_Not_Eqs:
			rel = make_efunc2("!=", rel, rel_new);
			break;
		default:
			break;
		}
		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return rel;
}

/*
expr_relational -> expr_shift
	| expr_relational '<' expr_shift
	| expr_relational '>' expr_shift
	| expr_relational LE expr_shift
	| expr_relational GE expr_shift
*/
static FinCNode* proc_relational_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* shift;
	FinCNode* shift_new;

	shift = proc_shift_expr(self);

	next_token(token, self->lex);
	while ( token == FinCTokenType_GT ||
		token == FinCTokenType_LT ||
		token == FinCTokenType_Greater_Eqs ||
		token == FinCTokenType_Less_Eqs )
	{
		shift_new = proc_shift_expr(self);
		switch (token)
		{
		case FinCTokenType_GT:
			shift = make_efunc2(">", shift, shift_new);
			break;
		case FinCTokenType_LT:
			shift = make_efunc2("<", shift, shift_new);
			break;
		case FinCTokenType_Greater_Eqs:
			shift = make_efunc2(">=", shift, shift_new);
			break;
		case FinCTokenType_Less_Eqs:
			shift = make_efunc2("<=", shift, shift_new);
			break;
		default:
			break;
		}
		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return shift;
}

/*
expr_shift -> expr_additive
	| expr_shift '<<' expr_additive
	| expr_shift '>>' expr_additive
*/
static FinCNode* proc_shift_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* add;
	FinCNode* add_new;

	add = proc_additive_expr(self);

	next_token(token, self->lex);
	while ( token == FinCTokenType_SHL || token == FinCTokenType_SHR )
	{
		add_new = proc_additive_expr(self);
		switch (token)
		{
		case FinCTokenType_SHL:
			add = make_efunc2("<<", add, add_new);
			break;
		case FinCTokenType_SHR:
			add = make_efunc2(">>", add, add_new);
			break;
		default:
			break;
		}
		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return add;
}

/**
expr_additive -> expr_multiplicative
	| expr_additive SUB expr_multiplicative
	| expr_additive ADD expr_multiplicative
*/
static FinCNode* proc_additive_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* mul;
	FinCNode* mul_new;

	mul = proc_multiplicative_expr(self);

	next_token(token, self->lex);
	while ( token == FinCTokenType_Sub || token == FinCTokenType_Add )
	{
		mul_new = proc_multiplicative_expr(self);
		switch (token)
		{
		case FinCTokenType_Sub:
			mul = make_efunc2("-", mul, mul_new);
			break;
		case FinCTokenType_Add:
			mul = make_efunc2("+", mul, mul_new);
			break;
		default:
			break;
		}
		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return mul;
}

/**
expr_multiplicative -> expr_cast
	| expr_multiplicative '*' expr_cast
	| expr_multiplicative '/' expr_cast
	| expr_multiplicative '%' expr_cast
*/
static FinCNode* proc_multiplicative_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* cast;
	FinCNode* cast_new;

	cast = proc_cast_expr(self);
	next_token(token, self->lex);
	while (token == FinCTokenType_Mul ||
		token == FinCTokenType_Div ||
		token == FinCTokenType_Mod )
	{
		cast_new = proc_cast_expr(self);
		switch (token)
		{
		case FinCTokenType_Mul:
			cast = make_efunc2("*", cast, cast_new);
			break;

		case FinCTokenType_Div:
			cast = make_efunc2("/", cast, cast_new);
			break;

		case FinCTokenType_Mod:
			cast = make_efunc2("%", cast, cast_new);
			break;
		default:
			finc_lang_error_line(self->lex, "Parser Error:unexpecting char in expr.");
			finc_context_error_inc(g_finc_context);
			break;
		}
		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return cast;
}

/**
expr_cast -> expr_unary
	| '(' type ')' expr_cast
*/
static FinCNode* proc_cast_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* type;
	FinCNode* cast;

	next_token(token, self->lex);
	if (token == FinCTokenType_Left_Brace)
	{
		type = proc_type(self);
		match_token(token, self->lex, FinCTokenType_Right_Brace);

		cast = proc_cast_expr(self);
		return make_efunc2("cast", type, cast);
	}
	else
	{
		finc_token_replay(self->lex);
		return proc_unary_expr(self);
	}
}

/**
expr_unary -> expr_postfix
	| ADD expr_cast
	| INC expr_cast
	| SUB expr_cast
	| DEC expr_cast
	| NOT expr_cast
	| '~' expr_cast
	| ADDR_OF '(' expr_unary ')'
	| VALUE_OF '(' expr_unary ')'
*/
static FinCNode* proc_unary_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* cast;
	FinCNode* unary;

	next_token(token, self->lex);
	switch (token)
	{
	case FinCTokenType_Add:
		cast = proc_cast_expr(self);
		return make_efunc1("plus", cast);

	case FinCTokenType_Inc:
		cast = proc_cast_expr(self);
		return make_efunc1("preinc", cast);

	case FinCTokenType_Sub:
		cast = proc_cast_expr(self);
		return make_efunc1("negative", cast);
		
	case FinCTokenType_Dec:
		cast = proc_cast_expr(self);
		return make_efunc1("predec", cast);
		
	case FinCTokenType_Not:
		cast = proc_cast_expr(self);
		return make_efunc1("!", cast);
		
	case FinCTokenType_Bitwise:
		cast = proc_cast_expr(self);
		return make_efunc1("~", cast);
		
	case FinCTokenType_Addrof:
		match_token(token, self->lex, FinCTokenType_Left_Paren);
		unary = proc_unary_expr(self);
		match_token(token, self->lex, FinCTokenType_Right_Paren);

		return make_efunc1("addr_of", unary);

	case FinCTokenType_Valueof:
		match_token(token, self->lex, FinCTokenType_Left_Paren);
		unary = proc_unary_expr(self);
		match_token(token, self->lex, FinCTokenType_Right_Paren);

		return make_efunc1("value_of", unary);

	default:
		finc_token_replay(self->lex);
		return proc_postfix_expr(self);
	}
	
	return NULL;
}

/**
expr_postfix -> expr_primary
	| expr_postfix '[' expr ']'
	| expr_postfix INC
	| expr_postfix DEC
	| expr_postfix '.' identifier
	| expr_postfix '(' param_list ')'
*/
static FinCNode* proc_postfix_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* postfix;
	FinCNode* id;
	FinCNode* expr;

	postfix = proc_primary_expr(self);

	next_token(token, self->lex);
	while ( token == FinCTokenType_Left_Brace ||
		token == FinCTokenType_Inc ||
		token == FinCTokenType_Dec ||
		token == FinCTokenType_Dot ||
		token == FinCTokenType_Left_Paren )
	{
		switch (token)
		{
		case FinCTokenType_Left_Brace :/* '[' */
			expr = proc_expr(self);
			match_token(token, self->lex, FinCTokenType_Right_Brace);
			postfix = make_efunc2("[]", postfix, expr);
			break;

		case FinCTokenType_Inc :/* '++' */
			postfix = make_efunc1("++", postfix);
			break;
		case FinCTokenType_Dec :/* '--' */
			postfix = make_efunc1("--", postfix);
			break;
		case FinCTokenType_Dot :/* '.' */
			id = proc_identifier(self);
			postfix = make_efunc2(".", postfix,  id);
			break;
		case FinCTokenType_Left_Paren :/* '(' */
			make_call_begin(self, string_get_str(postfix->identifier));
			unref(postfix);

			next_token(token, self->lex);
			if (token != FinCTokenType_Right_Paren )
			{
				finc_token_replay(self->lex);
				proc_call_param_list(self);
				
				match_token(token, self->lex, FinCTokenType_Right_Paren);
			}

			postfix = make_call_finish(self);
			break;
		default:
			break;
		}

		next_token(token, self->lex);
	}

	finc_token_replay(self->lex);
	return postfix;
}

/*
expr_primary -> literal
	| '(' expr ')'
	| identifier
*/
static FinCNode* proc_primary_expr(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* expr;

	next_token(token, self->lex);
	switch ( token )
	{
	case FinCTokenType_Identifier:
		finc_token_replay(self->lex);
		return proc_identifier(self);
	case FinCTokenType_Left_Paren:
		expr = proc_expr(self);
		match_token(token, self->lex, FinCTokenType_Right_Paren);
		return expr;
	case FinCTokenType_Int:
		return finc_node_new_integer((int)self->lex->last_double);
	#ifdef USING_FLOAT
	case FinCTokenType_Float:
		return finc_node_new_float((float)self->lex->last_float);
	#endif
	#ifdef USING_DOUBLE
	case FinCTokenType_Double:
		return finc_node_new_double((long)self->lex->last_double);
	#endif
	case FinCTokenType_Long:
		return finc_node_new_long((long)self->lex->last_double);
	case FinCTokenType_Char:
		return finc_node_new_char(self->lex->last_char);
	case FinCTokenType_String:
		return finc_node_new_string(string_get_str(self->lex->last_str));
	case FinCTokenType_Null:
		return finc_node_new_pointer(NULL);
	case FinCTokenType_True:
		return finc_node_new_bool(TRUE);
	case FinCTokenType_False:
		return finc_node_new_bool(FALSE);
	default:
		finc_token_replay(self->lex);
		break;
	}

	return NULL;
}

/*
param_list -> empty
	| expr_assign
	| param_list ',' expr_assign
*/
static FinCNode* proc_call_param_list(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* assign;

	assign = proc_assign_expr(self);
	make_call_add (self, assign);

	next_token(token, self->lex);
	while (token == FinCTokenType_Comma )
	{
		assign = proc_assign_expr(self);
		next_token(token, self->lex);

		make_call_add (self, assign);
	}

	finc_token_replay(self->lex);
	return NULL;
}

/*
statement -> decl_local
	| statement_block
	| statement_expr
	| statement_return
	| statement_for
	| statement_while
	| statement_if
	| statement_continue
	| statement_break
*/
static FinCNode* proc_statement(FinCParser* self)
{
	FinCTokenType token;
	String* str;

	next_token(token, self->lex);
	switch ( token )
	{
	case FinCTokenType_Left_Curly:
		finc_token_replay(self->lex);
		return proc_block_statement(self);
		break;

	case FinCTokenType_Return:
	case FinCTokenType_Continue:
	case FinCTokenType_Break:
		finc_token_replay(self->lex);
		return proc_simple_statement(self);
		break;

	case FinCTokenType_For:
		finc_token_replay(self->lex);
		return proc_for_statement(self);
		break;

	case FinCTokenType_While:
		finc_token_replay(self->lex);
		return proc_while_statement(self);
		break;

	case FinCTokenType_If:
		finc_token_replay(self->lex);
		return proc_if_statement(self);
		break;

	default:
		if (is_type(token))
		{
			if ( token == FinCTokenType_Identifier ) /*if it's a function call.*/
			{
				str = finc_token_get_token(self->lex);
				if (finc_lang_check_type(self->lang_env, str))/*it's a struct type.*/
				{
					unref(str);
					finc_token_replay(self->lex);
					return make_efunc1("local", proc_variable_decl(self));
				}
				else/*it's a function call.*/
				{
					unref(str);
					finc_token_replay(self->lex);
					return proc_expr_statement(self);
				}
			}

			finc_token_replay(self->lex);
			return make_efunc1("local", proc_variable_decl(self));
		}

		finc_lang_error_line(self->lex, "Parser Error: unexpecting token.");
		finc_context_error_inc(g_finc_context);
		finc_token_replay(self->lex);
		break;
	}

	return NULL;
}

/*
statement_in_block -> decl_local
	| statement_block
	| statement_node
	| statement_return
	| statement_for
	| statement_while
	| statement_if
*/
static FinCNode* proc_in_block_statement(FinCParser* self)
{
	FinCTokenType token;
	String* str;

	next_token(token, self->lex);
	switch ( token )
	{
	case FinCTokenType_Left_Curly:
		finc_token_replay(self->lex);
		return proc_block_statement(self);
		break;

	case FinCTokenType_Return:
	case FinCTokenType_Continue:
	case FinCTokenType_Break:
		finc_token_replay(self->lex);
		return proc_simple_statement(self);
		break;

	case FinCTokenType_For:
		finc_token_replay(self->lex);
		return proc_for_statement(self);
		break;

	case FinCTokenType_While:
		finc_token_replay(self->lex);
		return proc_while_statement(self);
		break;

	case FinCTokenType_If:
		finc_token_replay(self->lex);
		return proc_if_statement(self);
		break;

	default:
		if (is_type(token))
		{
			if ( token == FinCTokenType_Identifier ) /*if it's a function call.*/
			{
				str = finc_token_get_token(self->lex);
				if (finc_lang_check_type(self->lang_env, str))/*it's a struct type.*/
				{
					unref(str);
					finc_token_replay(self->lex);
					return make_efunc1("local", proc_variable_decl(self));
				}
				else/*it's a function call.*/
				{
					unref(str);
					finc_token_replay(self->lex);
					return proc_expr_statement(self);
				}
			}

			finc_token_replay(self->lex);
			return make_efunc1("local", proc_variable_decl(self));
		}

		finc_lang_error_line(self->lex, "Parser Error: unexpecting token.");
		finc_context_error_inc(g_finc_context);
		finc_token_replay(self->lex);
		break;
	}

	return NULL;
}

/*
statement_block -> '{' statement_list '}'
statement_list -> statement_in_block
	| statement_list statement_in_block
*/
static FinCNode* proc_block_statement(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* statement;

	match_token(token, self->lex, FinCTokenType_Left_Curly);
	make_block_begin(self);

	next_token(token, self->lex);
	while (token != FinCTokenType_Right_Curly)
	{
		finc_token_replay(self->lex);
		statement = proc_in_block_statement(self);
		if (statement)
		{
			make_block_add(self, statement);
			next_token(token, self->lex);
		}
		else break;
	}

	return make_block_finish(self);
}

/*
statement_expr -> ';'
	| expr ';'
*/
static FinCNode* proc_expr_statement(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* expr;

	expr = NULL;
	next_token(token, self->lex);
	if ( token != FinCTokenType_Semicolon )
	{
		finc_token_replay(self->lex);
		expr = proc_expr(self);

		match_token(token, self->lex, FinCTokenType_Semicolon);
	}

	return expr;
}

/*
statement_for -> FOR '(' statement_expr statement_expr expr ')' statement
*/
static FinCNode* proc_for_statement(FinCParser* self)
{
	FinCTokenType token;
	FinCNode *expr_s1, *expr_s2, *expr, *statement;

	expr = NULL;
	match_token(token, self->lex, FinCTokenType_For);
	match_token(token, self->lex, FinCTokenType_Left_Paren);

	expr_s1 = proc_expr_statement(self);

	expr_s2 = proc_expr_statement(self);

	next_token(token, self->lex);
	if (token != FinCTokenType_Right_Paren)
	{
		finc_token_replay(self->lex);
		expr = proc_expr(self);
		match_token(token, self->lex, FinCTokenType_Right_Paren);
	}

	statement = proc_statement(self);

	return make_efunc4 ("for", expr_s1, expr_s2, expr, statement);
}

/*
statement_while -> WHILE '(' expr ')' statement
*/
static FinCNode* proc_while_statement(FinCParser* self)
{
	FinCTokenType token;
	FinCNode *expr, *statement;

	match_token(token, self->lex, FinCTokenType_While);
	match_token(token, self->lex, FinCTokenType_Left_Paren);

	expr = proc_expr(self);

	match_token(token, self->lex, FinCTokenType_Right_Paren);

	statement = proc_statement(self);

	return make_efunc2 ("while", expr, statement);
}

/*
statement_if -> IF '(' expr ')' statement statement_if_else
statement_if_else -> empty
	| ELSE statement
*/
static FinCNode* proc_if_statement(FinCParser* self)
{
	FinCTokenType token;
	FinCNode *expr, *statement_true, *statement_false;

	statement_false = NULL;

	match_token(token, self->lex, FinCTokenType_If);
	match_token(token, self->lex, FinCTokenType_Left_Paren);

	expr = proc_expr(self);

	match_token(token, self->lex, FinCTokenType_Right_Paren);

	statement_true = proc_statement(self);

	next_token(token, self->lex);
	if ( token == FinCTokenType_Else )
		statement_false = proc_statement(self);
	else finc_token_replay(self->lex);

	if ( statement_false )
	{
		return make_efunc3 ("if", expr, statement_true, statement_false);
	}
	else
	{
		return make_efunc2 ("if", expr, statement_true);
	}

	return NULL;
}

/*
statement_continue -> CONTINUE ';'
statement_break -> BREAK ';'
statement_return -> RETURN expr ';'
*/
static FinCNode* proc_simple_statement(FinCParser* self)
{
	FinCTokenType token;
	FinCNode* expr;

	expr = NULL;
	next_token(token, self->lex);

	switch ( token )
	{
	case FinCTokenType_Continue:
		match_token(token, self->lex, FinCTokenType_Semicolon);

		return make_efunc("continue");
		break;

	case FinCTokenType_Break:
		match_token(token, self->lex, FinCTokenType_Semicolon);

		return make_efunc("break");
		break;
	case FinCTokenType_Return:
		next_token(token, self->lex);
		if ( token != FinCTokenType_Semicolon )
		{
			finc_token_replay(self->lex);
			expr = proc_expr(self);
			next_token(token, self->lex);
		}
		check_token(token, self->lex, FinCTokenType_Semicolon);

		return make_efunc1("return", expr);
		break;
	default:
		break;
	}

	return NULL;
}

static void make_pkg_begin(FinCParser* self, unsigned char* p_package)
{
	FinCNode* pkg_name;
	pkg_name = finc_node_new_name(p_package);

    self->current_pkg = finc_node_new_func("package");
	finc_node_add(self->current_pkg, pkg_name);
	unref(pkg_name);
}

static void make_pkg_func_begin (FinCParser* self, FinCNode* p_type, FinCNode* p_identifier)
{
	self->current_func = finc_node_new_func ("func");

	finc_node_add (self->current_func, p_type);
	unref (p_type);

	finc_node_add (self->current_func, p_identifier);
	unref (p_identifier);
}

static FinCNode* make_pkg_func_finish (FinCParser* self)
{
	FinCNode* l_func;

	l_func = self->current_func;
	self->current_func = NULL;

	return l_func;
}

static FinCNode* make_pkg_finish(FinCParser* self)
{
	FinCNode* l_pkg;

	l_pkg = self->current_pkg;
	self->current_pkg = NULL;

	return l_pkg;
}

static void make_func_begin (FinCParser* self, FinCNode* p_type, FinCNode* p_identifier)
{
	self->current_func = finc_node_new_func ("func");

	finc_node_add (self->current_func, p_type);
	unref (p_type);

	finc_node_add (self->current_func, p_identifier);
	unref (p_identifier);
}

static void make_func_add_param (FinCParser* self, FinCNode* p_type, FinCNode* p_name)
{
	finc_node_add (self->current_func, p_type);
	unref (p_type);

	finc_node_add (self->current_func, p_name);
	unref (p_name);
}

static void make_func_opt_param (FinCParser* self)
{
	finc_node_add (self->current_func, NULL);
}

static FinCNode* make_func_finish (FinCParser* self, FinCNode* p_code)
{
	FinCNode* l_func;

	finc_node_add (self->current_func, p_code);
	unref (p_code);

	l_func = self->current_func;
	self->current_func = NULL;

	return l_func;
}

static void make_block_begin (FinCParser* self)
{
	if (self->current_block)
	{
		stack_push(self->stack_block, (ADT)self->current_block);
		unref(self->current_block);
	}
	self->current_block = finc_node_new_func ("@");
}

static void make_block_add (FinCParser* self, FinCNode* p_node)
{
	finc_node_add (self->current_block, p_node);
	unref (p_node);
}

static FinCNode* make_block_finish (FinCParser* self)
{
	FinCNode* l_block;

	if (stack_get_size(self->stack_block) > 0)
	{
		l_block = self->current_block;
		self->current_block = stack_pop(self->stack_block);
	}
	else
	{
		l_block = self->current_block;
		self->current_block = NULL;
	}

	return l_block;
}

static void make_call_begin (FinCParser* self, unsigned char* p_identifier)
{
	if (self->current_call)
	{
		stack_push(self->stack_call, (ADT)self->current_call);
		unref(self->current_call);
	}
	self->current_call = finc_node_new_func (p_identifier);
}

static void make_call_add (FinCParser* self, FinCNode* p_node)
{
	finc_node_add (self->current_call, p_node);
	unref (p_node);
}

static FinCNode* make_call_finish (FinCParser* self)
{
	FinCNode* l_call;

	if (stack_get_size(self->stack_call) > 0)
	{
		l_call = self->current_call;
		self->current_call = stack_pop(self->stack_call);
	}
	else
	{
		l_call = self->current_call;
		self->current_call = NULL;
	}

	return l_call;
}

static FinCNode* make_efunc (unsigned char* p_func)
{
	return finc_node_new_func (p_func);
}

static FinCNode* make_efunc1 (unsigned char* p_func, FinCNode* p_node1)
{
	FinCNode* l_node;

	l_node = finc_node_new_func (p_func);
	finc_node_add (l_node, p_node1);
	unref (p_node1);

	return l_node;
}

static FinCNode* make_efunc2 (unsigned char* p_func, FinCNode* p_node1, FinCNode* p_node2)
{
	FinCNode* l_node;

	l_node = finc_node_new_func (p_func);

	finc_node_add (l_node, p_node1);
	unref (p_node1);
	finc_node_add (l_node, p_node2);
	unref (p_node2);

	return l_node;
}

static FinCNode* make_efunc3 (unsigned char* p_func, FinCNode* p_node1, FinCNode* p_node2, FinCNode* p_node3)
{
	FinCNode* l_node;

	l_node = finc_node_new_func (p_func);

	finc_node_add (l_node, p_node1);
	unref (p_node1);
	finc_node_add (l_node, p_node2);
	unref (p_node2);
	finc_node_add (l_node, p_node3);
	unref (p_node3);

	return l_node;
}

static FinCNode* make_efunc4 (unsigned char* p_func, FinCNode* p_node1, FinCNode* p_node2, FinCNode* p_node3, FinCNode* p_node4)
{
	FinCNode* l_node;

	l_node = finc_node_new_func (p_func);

	finc_node_add (l_node, p_node1);
	unref (p_node1);
	finc_node_add (l_node, p_node2);
	unref (p_node2);
	finc_node_add (l_node, p_node3);
	unref (p_node3);
	finc_node_add (l_node, p_node4);
	unref (p_node4);

	return l_node;
}
