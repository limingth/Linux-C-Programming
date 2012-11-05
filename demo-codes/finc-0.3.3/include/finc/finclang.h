#ifndef _FinC_LANG_H_
#define _FinC_LANG_H_

#include <tiny/global.h>
#include <tiny/object.h>
#include <tiny/string.h>
#include <tiny/stack.h>
#include <tiny/library.h>

#include <finc/fincconfig.h>
#include <finc/fincnode.h>
#include <finc/finctoken.h>

typedef struct _FinCLangEnv FinCLangEnv;
struct _FinCLangEnv
{
    Object parent;
    
    FinCNode* tree_root;
    List* list_pkg;

#ifdef USING_PACKAGE
    LibFactory* libfactory;
#endif

    unsigned int nb_error;
};

extern FinCLangEnv* g_finc_lang_env;
extern int g_lang_nberr;

FinCLangEnv* finc_lang_new ();
void finc_lang_destroy(Object* self);

void finc_lang_error_line (FinCTokenEnv* lex, char* msg);

Bool finc_lang_check_type (FinCLangEnv* self, String* p_type);

#ifdef USING_PACKAGE
void finc_lang_proc_pkg (FinCLangEnv* self, FinCNode* p_node);
#endif

#ifdef USING_FILE
void finc_lang_proc_import(FinCLangEnv* self, FinCNode* p_node);
#endif

void finc_lang_proc_struct(FinCLangEnv* self, FinCNode* p_node);
void finc_lang_proc_func (FinCLangEnv* self, FinCNode* p_node );

#endif
