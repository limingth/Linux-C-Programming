#include <tiny/mem.h>

/*#define MEM_DEBUG*/

#ifdef MEM_DEBUG
typedef struct _MemNode MemNode;
typedef struct _MemChunk MemChunk;

struct _MemNode
{
	ADT data;
	MemNode *next, *prev;
};
struct _MemChunk
{
	MemNode* head;
};

static MemChunk* obj_head = NULL;

MemChunk* mem_chunk_new();
void mem_chunk_insert(MemChunk* self, ADT addr);
void mem_chunk_remove(MemChunk* self, ADT addr);
void mem_chunk_update(MemChunk* self, ADT src, ADT des);
void mem_chunk_debug(MemChunk* self);
void mem_chunk_destroy(MemChunk* self);
#endif

#ifdef __DOOLOO__
void *calloc(int nmemb, int _size)
{
	register int size=_size*nmemb;

	return malloc(size);
}

void *realloc(void* ptr, int _size)
{
	void *result;

	if ( _size > 0 )
	{
		result = malloc(_size);
		if(ptr)
		{
			memcpy(result, ptr, _size);
			free(ptr);
		}
	}
	else
	{
		if(ptr) free(ptr);
		return NULL;
	}

	return result;
}
#endif

static int obj_alloc = 0;
ADT mem_new (int p_size)
{
	ADT result;

	if (p_size)
	{
		obj_alloc++;
		result = (ADT) malloc (p_size);
		if ( result == NULL )
		{
			printf("Tiny Mem: Out of memory\n");
		}

#ifdef MEM_DEBUG
		if (!obj_head) obj_head = mem_chunk_new();
		mem_chunk_insert(obj_head, result);
#endif

		return result;
	}
	else
		return NULL;
}

ADT mem_resize (ADT p_ptr, int p_size)
{
	ADT result;

	if (p_ptr)
	{
		result = (ADT) realloc (p_ptr, p_size);
#ifdef MEM_DEBUG
		if (result != p_ptr)mem_chunk_update(obj_head, p_ptr, result);
#endif
		return result;
	}
	else
		return mem_new (p_size);
}

void mem_destroy (ADT p_ptr)
{
	if (p_ptr)
	{
		obj_alloc--;
#ifdef MEM_DEBUG
		mem_chunk_remove(obj_head, p_ptr);
#endif
		free (p_ptr);
		p_ptr = NULL;
	}
}

void mem_copy (ADT p_src, ADT p_dst, int p_size)
{
	memcpy (p_dst, p_src, p_size);
}

void mem_move (ADT p_src, ADT p_dst, int p_size)
{
	memmove (p_dst, p_src, p_size);
}

void mem_set (ADT s, char c, int size)
{
	memset(s, c, size);
}

void mem_debug ()
{
    if(obj_alloc !=0 )
	{
		printf ("unallocated objects = %d\n", obj_alloc);
#ifdef MEM_DEBUG
		mem_chunk_debug(obj_head);
#endif
	}
}

#ifdef MEM_DEBUG
MemChunk* mem_chunk_new()
{
	MemChunk* self;

	self = (MemChunk*)malloc(sizeof(MemChunk));
	self->head = NULL;

	return self;
}

MemNode* mem_node_new(ADT addr)
{
	MemNode* self;

	self = (MemNode*)malloc(sizeof(MemNode));

	self->data = addr;
	self->next = NULL;
	self->prev = NULL;

	return self;
}

void mem_chunk_insert(MemChunk* self, ADT addr)
{
	MemNode* insert;

	insert = mem_node_new(addr);

	if (self->head)
	{
		insert->next = self->head;
		self->head->prev = insert;
	}
	
	self->head = insert;
}

void mem_chunk_remove(MemChunk* self, ADT addr)
{
	MemNode* stand;

	stand = self->head;
	while (stand)
	{
		if (stand->data == addr)
		{
			if (stand->prev) stand->prev->next = stand->next;
			else self->head = stand->next;

			if (stand->next) stand->next->prev = stand->prev;

			free(stand);
			break;
		}
		stand = stand->next;
	}

//	fprintf(stderr, "mem block not found!\n");
}

void mem_chunk_update(MemChunk* self, ADT src, ADT des)
{
	MemNode* stand;

	stand = self->head;
	while (stand)
	{
		if (stand->data == src)
		{
			stand->data = des;
			break;
		}
		stand = stand->next;
	}
}

void mem_chunk_debug(MemChunk* self)
{
	MemNode* stand;

	stand = self->head;
	while (stand)
	{
		stand = stand->next;
	}
}

void mem_chunk_destroy(MemChunk* self)
{
	MemNode* stand;

	stand = self->head;
	while ( stand )
	{
		if (stand->next)
		{
			stand = stand->next;
			free(stand->prev);
		}
		else
		{
			free(stand);
		}
	}

	free(self);
}
#endif
