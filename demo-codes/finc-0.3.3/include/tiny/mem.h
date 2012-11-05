#ifndef __MEM_H_
#define __MEM_H_

#include <tiny/global.h>

#ifdef __DOOLOO__
#include <memory.h>
#endif

ADT mem_new (int p_size);

ADT mem_resize (ADT p_ptr, int p_size);

void mem_destroy (ADT p_ptr);

void mem_copy (ADT p_src, ADT p_dst, int p_size);

void mem_move (ADT p_src, ADT p_dst, int p_size);

void mem_set (ADT s, char c, int size);

void mem_debug ();

#endif
