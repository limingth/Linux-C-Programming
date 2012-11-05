#include <tiny/list.h>

struct _ListNode
{
	ADT data;
	struct _ListNode* prev;
	struct _ListNode* next;
};
typedef struct _ListNode ListNode;

struct _RealList
{
	Object parent;
	ListNode* current;

	int length;
	ListNode* head;
	ListNode* tail;
};
typedef struct _RealList RealList;

static ListNode* list_new_node()
{
	ListNode* node;

	node = (ListNode*) mem_new (sizeof(ListNode));
	node->data = NULL;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

List* list_new()
{
	RealList* l_reallist = (RealList*) mem_new (sizeof(RealList));
	object_init_object (OBJECT(l_reallist), list_destroy);
	l_reallist->length=0;
	l_reallist->head=NULL;
	l_reallist->tail=NULL;

	return (List*)l_reallist;
}

void list_destroy(Object* self)
{
	RealList* l_reallist = (RealList*)self;
	list_clear((List*)self);

	mem_destroy(l_reallist);
}

void list_clear(List* self)
{
	RealList* l_reallist = (RealList*)self;
	ListNode* l_stand = l_reallist->head;
	while ( l_stand )
	{
		if ( l_stand->next )
		{
			l_stand=l_stand->next;

			unref(l_stand->prev->data);
			mem_destroy(l_stand->prev);
		}
		else
		{
			unref(l_stand->data);
			mem_destroy(l_stand);
			break;
		}
	}

	l_reallist->length=0;
	l_reallist->head=NULL;
	l_reallist->tail=NULL;
	l_reallist->current=NULL;
}

Bool list_is_empty(List* self)
{
	return ((RealList*)self)->length==0? TRUE:FALSE;
}

int list_get_size(List* self)
{
	return ((RealList*)self)->length;
}

int list_current(List* self)
{
	RealList* l_reallist = (RealList*)self;

	ListNode* l_stand = l_reallist->head;
	int i=0;
	while ( l_stand!= l_reallist->current )
	{
		i++;
		l_stand = l_stand->next;
	}
	
	return i;
}

ADT list_at(List* self, int p_index)
{
	RealList* l_reallist = (RealList*)self;
	int i;

	if ( p_index <=0 || p_index > l_reallist->length )
	{
		return NULL;
	}

	l_reallist->current = l_reallist->head;
	for ( i=0 ; i<p_index ; i++)
	{
		l_reallist->current = l_reallist->current->next;
	}

	return addref(ADT, l_reallist->current->data);
}

Bool list_locate(List* self, int p_index)
{
	RealList* l_reallist = (RealList*)self;
	int i;

	if ( p_index <=0 || p_index > l_reallist->length )
		return FALSE;

	l_reallist->current = l_reallist->head;
	for ( i=0; i<p_index ; i++) l_reallist->current = l_reallist->current->next;

	return TRUE;
}

ADT list_data(List* self)
{
	RealList* l_reallist = (RealList*)self;

	return l_reallist->current? addref(ADT, l_reallist->current->data):NULL;
}

ADT list_take(List* self, int p_index)
{
	if ( list_at(self, p_index) )
	{
		return list_take_current(self);
	}

	return NULL;
}

ADT list_take_current(List* self)
{
	RealList* l_reallist = (RealList*)self;
	ListNode* l_stand;
	ADT rtn = NULL;

	if ( l_reallist->current == NULL )return NULL;

	l_stand = l_reallist->current;
	if ( l_stand->prev ) l_stand->prev->next = l_stand->next;
	else l_reallist->head = l_stand->next;

	if ( l_stand->next ) l_stand->next->prev = l_stand->prev;
	else l_reallist->tail = l_stand->prev;

	if ( l_stand->next )l_reallist->current = l_stand->next;
	else l_reallist->current = l_stand->prev;

	mem_destroy(l_stand);

	l_reallist->length--;

	return addref(ADT, rtn);
}

ADT list_find(List* self, EqualFunc p_func, ADT p_data)
{
	RealList* l_reallist = (RealList*)self;
	ListNode* l_stand;

	l_stand = l_reallist->head;

	while ( l_stand != NULL )
	{
		if ( p_func )
		{
			if ( (*p_func)(l_stand->data, p_data) )
			{
				l_reallist->current = l_stand;
				return addref(ADT, l_stand->data);
			}
		}
		else
		{
			if ( l_stand->data == p_data )
			{
				l_reallist->current = l_stand;
				return addref(ADT, l_stand->data);
			}
		}
		
		l_stand = l_stand->next;
	}

	return NULL;
}

ADT list_find_ref(List* self, EqualFunc p_func, ADT p_data)
{
	RealList* l_reallist = (RealList*)self;
	ListNode* l_stand;

	l_stand = l_reallist->tail;

	while ( l_stand != NULL )
	{
		if ( p_func )
		{
			if ( (*p_func)(l_stand->data, p_data) )
			{
				l_reallist->current = l_stand;
				return addref(ADT, l_stand->data);
			}
		}
		else
		{
			if ( l_stand->data == p_data )
			{
				l_reallist->current = l_stand;
				return addref(ADT, l_stand->data);
			}
		}

		l_stand = l_stand->prev;
	}

	return NULL;
}

void list_insert(List* self, int p_index, ADT p_src)
{
	RealList* l_reallist = (RealList*)self;

	if ( p_index<=0 || p_index>l_reallist->length )
	{
		list_append(self, p_src);
		return ;
	}

	if ( list_locate(self, p_index) ) list_insert_after(self, p_src);
	else list_append(self, p_src);
}

void list_insert_before(List* self, ADT p_data)
{
	RealList* l_reallist = (RealList*)self;
	ListNode* l_node;
	
	l_node = list_new_node();
	l_node->data = addref(ADT, p_data);

	if ( l_reallist->current )
	{
		if ( l_reallist->current->prev )
		{
			l_node->prev = l_reallist->current->prev;
			l_reallist->current->prev->next = l_node;
		}
		else
		{/*if the current node is head.*/
			l_reallist->head = l_node;
		}

		l_node->next = l_reallist->current;
		l_reallist->current->prev = l_node;
	}
	else
	{/*if the self is empty.*/
		l_reallist->head = l_node;
		l_reallist->tail = l_node;
	}

	l_reallist->current = l_node;
	l_reallist->length++;
}

void list_insert_after(List* self, ADT p_data)
{
	RealList* l_reallist = (RealList*)self;
	ListNode* l_node;

	l_node = list_new_node();
	l_node->data = addref(ADT, p_data);

	if ( l_reallist->current )
	{
		if ( l_reallist->current->next )
		{
			l_node->prev = l_reallist->current->next;
			l_reallist->current->next->prev = l_node;
		}
		else
		{/*if the current node is tail*/
			l_reallist->tail = l_node;
		}

		l_node->prev = l_reallist->current;
		l_reallist->current->next = l_node;
	}
	else
	{/*if the self is empty.*/
		l_reallist->head = l_node;
		l_reallist->tail = l_node;
	}

	l_reallist->current = l_node;
	l_reallist->length++;
}

void list_prepend(List* self, ADT p_data)
{
	RealList* l_reallist = (RealList*)self;
	l_reallist->current = l_reallist->head;

	list_insert_before(self, p_data);
}

void list_append(List* self, ADT p_data)
{
	RealList* l_reallist = (RealList*)self;
	l_reallist->current = l_reallist->tail;

	list_insert_after(self, p_data);
}

void list_remove(List* self, int p_index)
{
	if ( list_locate(self, p_index) )
		list_remove_current(self);
}

void list_remove_ref(List* self, EqualFunc p_func, ADT p_data)
{
	if ( list_find_ref(self, p_func, p_data) )
		list_remove_current(self);
}

void list_remove_current(List* self)
{
	RealList* l_reallist = (RealList*)self;
	ListNode* l_stand;

	if ( l_reallist->current == NULL )return ;

	l_stand = l_reallist->current;
	if ( l_stand->prev )
		l_stand->prev->next = l_stand->next;
	else
		l_reallist->head = l_stand->next;

	if ( l_stand->next )
	{
		l_stand->next->prev = l_stand->prev;
		l_reallist->current = l_stand->next;
	}
	else
	{
		l_reallist->tail = l_stand->prev;
		l_reallist->current = l_stand->prev;
	}

	unref(l_stand->data);
	mem_destroy(l_stand);

	l_reallist->length--;
}

ADT list_prev(List* self)
{
	RealList* l_reallist = (RealList*)self;

	if ( l_reallist->current )//if the self is not empty.
	{
		if ( l_reallist->current->prev )
		{
			l_reallist->current = l_reallist->current->prev;
			return addref(ADT, l_reallist->current->data);
		}
	}

	return NULL;
}

ADT list_next(List* self)
{
	RealList* l_reallist = (RealList*)self;

	if ( l_reallist->current )//if the self is not empty.
	{
		if ( l_reallist->current->next )
		{
			l_reallist->current = l_reallist->current->next;
			return addref(ADT, l_reallist->current->data);
		}
	}

	return NULL;
}

ADT list_prev_unref(List* self)
{
	RealList* l_reallist = (RealList*)self;

	if ( l_reallist->current )//if the self is not empty.
	{
		if ( l_reallist->current->prev )
		{
			l_reallist->current = l_reallist->current->prev;
			return l_reallist->current->data;
		}
	}

	return NULL;
}

ADT list_next_unref(List* self)
{
	RealList* l_reallist = (RealList*)self;

	if ( l_reallist->current )//if the self is not empty.
	{
		if ( l_reallist->current->next )
		{
			l_reallist->current = l_reallist->current->next;
			return l_reallist->current->data;
		}
	}

	return NULL;
}

ADT list_first(List* self)
{
	RealList* l_reallist = (RealList*)self;

	if ( l_reallist->head )//if the self is not empty.
	{
		l_reallist->current = l_reallist->head;
		return addref(ADT, l_reallist->current->data);
	}

	return NULL;
}

ADT list_last(List* self)
{
	RealList* l_reallist = (RealList*)self;

	if ( l_reallist->head )//if the self is not empty.
	{
		l_reallist->current = l_reallist->tail;
		return addref(ADT, l_reallist->current->data);
	}

	return NULL;
}

ADT list_first_unref(List* self)
{
	RealList* l_reallist = (RealList*)self;

	if ( l_reallist->head )//if the self is not empty.
	{
		l_reallist->current = l_reallist->head;
		return l_reallist->current->data;
	}

	return NULL;
}

ADT list_last_unref(List* self)
{
	RealList* l_reallist = (RealList*)self;

	if ( l_reallist->head )//if the self is not empty.
	{
		l_reallist->current = l_reallist->tail;
		return l_reallist->current->data;
	}

	return NULL;
}

void list_foreach(List* self, UserFunc p_function, ADT p_data)
{
	RealList* l_reallist = (RealList*)self;
	ListNode* l_stand = l_reallist->head;

	while ( l_stand )
	{
		(*p_function)(l_stand->data, p_data);
		l_stand = l_stand->next;
	}
}
