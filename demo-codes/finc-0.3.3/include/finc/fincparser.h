#ifndef _FinC_PARSER_H
#define _FinC_PARSER_H

#include <tiny/object.h>
#include <tiny/string.h>

#include <finc/fincconfig.h>
#include <finc/fincnode.h>
#include <finc/finctoken.h>
#include <finc/finclang.h>
#include <finc/fincsys.h>

typedef struct _FinCParser FinCParser;
struct _FinCParser
{
    Object parent;
    FinCNode* tree_root;
    FinCTokenEnv* lex;
    
    String* parse_string;

    FinCLangEnv* lang_env;
    
    Stack* stack_call;
    Stack* stack_block;

    FinCNode* current_func;
    FinCNode* current_block;
    FinCNode* current_call;
    FinCNode* current_type;
    FinCNode* current_pkg;
    FinCNode* current_struct;
	FinCNode* current_class;
};

FinCParser* finc_parser_new();
void finc_parser_destroy(Object* self);
void finc_parser_set_env (FinCParser* self, FinCLangEnv* env);

void finc_parser_parser(FinCParser* self, String* stream);
void finc_parser_parser_string(FinCParser* self, String* str);

#ifdef USING_FILE
void finc_parser_parser_file(FinCParser* self, const char* filename);
#endif

#endif
