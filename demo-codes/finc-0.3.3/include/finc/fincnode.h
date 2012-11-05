#ifndef _FINC_NODE_H_
#define _FINC_NODE_H_

#include <tiny/global.h>
#include <tiny/object.h>
#include <tiny/string.h>

#include <finc/fincconfig.h>
#include <finc/fincdata.h>

typedef struct _FinCFunc FinCFunc;
typedef struct _FinCNode FinCNode;

#include <finc/fincfunc.h>

#define FinC_NODE(obj) ((FinCNode*) obj)

typedef enum
{
	FinCNodeType_None,
	FinCNodeType_Block,
	FinCNodeType_Data,
	FinCNodeType_Func,
	FinCNodeType_Type,
	FinCNodeType_Identifier
} FinCNodeType;

struct _FinCNode
{
    Object parent;

    FinCNodeType node_type;
    FinCData* data;
    FinCFunc* func;
    FinCType* type;
    String* identifier;
    Bool check;
    Bool constant;
    
    String* source_file;
    unsigned int source_line;

    Vector* vector_node;
};

FinCNode* finc_node_new ();
FinCNode* finc_node_new_func (unsigned char* p_name);
FinCNode* finc_node_new_name (unsigned char* p_name);
FinCNode* finc_node_new_type (String* p_typename, FinCArrayType p_array, unsigned int p_size);
FinCNode* finc_node_new_char (unsigned char p_char);
FinCNode* finc_node_new_string (unsigned char* p_text);
FinCNode* finc_node_new_integer (unsigned int p_int);
#ifdef USING_FLOAT
FinCNode* finc_node_new_float (float p_value);
#endif
#ifdef USING_DOUBLE
FinCNode* finc_node_new_double (double p_value);
#endif
FinCNode* finc_node_new_long (long p_long);
FinCNode* finc_node_new_bool (Bool p_bool);
FinCNode* finc_node_new_pointer (void* p_ptr);

void finc_node_destroy (Object* self);

#define finc_node_add(node1, node2) vector_append ((node1)->vector_node, (Object*)(node2))
#define finc_node_check(node, type) (node)->node_type == (type)? TRUE : FALSE

void finc_node_evaluate (FinCNode* self);

#define finc_node_get( node, index) (FinCNode*)vector_at( (node)->vector_node, (index) )
#define finc_node_get_size( node ) vector_get_size( (node)->vector_node )

FinCData* finc_node_take_data (FinCNode* self);

#define finc_node_set_constant(node) (node)->constant = TRUE
#define finc_node_set_block(node) (node)->node_type = FinCNodeType_Block

void finc_node_set_data (FinCNode* self, FinCData* p_data);
void finc_node_set_func (FinCNode* self, String* p_name);
void finc_node_set_type (FinCNode* self, FinCType* p_type);
void finc_node_set_identifier (FinCNode* self, String* p_identifier);

#endif
