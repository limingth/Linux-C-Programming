#ifndef _FINC_DEBUG_H_
#define _FINC_DEBUG_H_

#include <tiny/string.h>

#include <finc/fincconfig.h>

#ifdef FINC_DEBUG
#include <finc/fincnode.h>
#include <finc/fincdata.h>

void finc_debug_node (FinCNode* p_node);
void finc_debug_data (char* msg, FinCData* p_data);
void finc_debug_var (char* p_var);
#endif

#endif
