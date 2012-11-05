#ifndef __LIST_H_
#define __LIST_H_

#include <tiny/global.h>

#define LIST(obj) ((List*) obj)

typedef struct _List List;
/*
* initial a list
* return a initialed list.
*/
List* list_new();
/*
* delete a list, the list will be free.
*/
void  list_destroy(Object* self);

/*
* clear a list, include the free_list.
*/
void list_clear(List* self);
/*
* if the list is empty, return true.
*/
Bool list_is_empty(List* self);

/*
* return the list length.
*/
int list_get_size(List* self);

/*
* return the list current sequence.
*/
int list_current(List* self);
/*
* return the list ith node data, and it also will put the current point to that.
*/
ADT list_at(List* self, int p_index);
Bool list_locate(List* self, int p_index);

/*
* return the list current node data.
*/
ADT list_data(List* self);

/*
* return the list ith node data, and remove the node from list.
*/
ADT list_take(List* self, int p_index);
/*
* return the list current node data, and remove the node from list.
*/
ADT list_take_current(List* self);

/*
* find the data in list.
*/
ADT list_find(List* self, EqualFunc p_func, ADT p_data);
/*
* find the data in list.
*/
ADT list_find_ref(List* self, EqualFunc p_func, ADT p_data);

/*
* insert data to the list ith.
*/
void list_insert(List* self, int p_index, ADT p_data);
/*
* insert data to before of the list current node.
*/
void list_insert_before(List* self, ADT p_data);
/*
* insert data to after of the list current node.
*/
void list_insert_after(List* self, ADT p_data);

/*
* prepend the date to the list.
*/
void list_prepend(List* self, ADT p_data);
/*
* append the data to the list.
*/
void list_append(List* self, ADT p_data);

/*
* remove the list ith node and free its data.
*/
void list_remove(List* self, int p_index);
/*
* remove the list node include data, and find data use function: compare.
* it is also free the data.
*/
void list_remove_ref(List* self, EqualFunc p_func, ADT p_data);
/*
* remove the list current node and free its data.
*/
void list_remove_current(List* self);

/*
* get the list preview data, and move the current node point to preview node.
* if the preview data is NULL, it will return NULL and not move the current node point.
*/
ADT list_prev(List* self);
ADT list_prev_unref(List* self);

/*
* get the list next data, and move the current node point to next node.
* if the next data is NULL, it will return NULL and not move the current node point.
*/
ADT list_next(List* self);
ADT list_next_unref(List* self);

/*
* get the list first data, and move the current node point to first node.
*/
ADT list_first(List* self);
ADT list_first_unref(List* self);

/*
* get the list last data, and move the current node point to last node.
*/
ADT list_last(List* self);
ADT list_last_unref(List* self);

/*
* use function: function for each list node.
*/
void list_foreach(List* self, UserFunc p_func, ADT data);

#endif
