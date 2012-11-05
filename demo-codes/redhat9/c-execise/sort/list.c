#include "list.h"
#include "stdlib.h"
#include "assert.h"

/* define the head node of link list */
lnode * head = NULL;
lnode * tail= NULL;

/*
 * list insert - insert anode to link list  
 * input - anode : the node pointer to insert 
 * output - add anode to its proper position
 *
 */
int list_insert( lnode * anode )
{
	int ret = 0;		
	lnode * current;	/* define the current node */
	lnode * prev;		/* define the previous node */

	/* assert the anode is valid and NOT null pointer */
	assert( anode );	

	printf( "adding anode : %s \n", anode->pline );
	//printf( "adding anode pline: 0x%x \n", anode->pline );

	/* if there is none node in the list */
	if( head == NULL )
	{
		head = anode;
		tail = anode;
		printf( "head = 0x%x \n", head );
		printf( "tail = 0x%x \n", tail );
		return 0;
	}

#define M1 1	
#ifdef M1
	/* set current as the head of list */
	prev = head;
	current = head;

	/* try to fine anode 's proper position */
	do
	{
		printf( "cmp: %s vs %s \n", current->pline, anode->pline );
		/* compare the two node */
		ret = strcmp( current->pline, anode->pline );
		printf( "ret = %d \n", ret );

		/* judge which one is bigger */
		if( ret == -1 )
		{
			printf( "anode is bigger, then next \n" );
			/* anode is bigger, then next */
			prev = current;
			current = current->next;
		}
		else
		{
			printf( "anode is smaller, insert it \n" );
			/* anode is smaller, then insert */
			/* case 1: insert before head */
			if( current == head )
			{
				anode->next = head;
				head = anode;
			}
			/* case 2: insert after head */
			else
			{
				prev->next = anode;
				anode->next = current;	
			}
			return;
		}
	} while( current );

	/* if current is NULL, then insert it as the tail */
	prev->next = anode;
	tail = anode;

	return;

#if 0
	while( current ) 
	{
		printf( "cmp: %s vs %s \n", current->pline, anode->pline );
		ret = strcmp( current->pline, anode->pline );
		printf( "ret = %d \n", ret );

		/* ret == -1, anode is bigger, then next */
		if( ret == -1 )
		{
			printf( "anode is bigger, then next \n" );
			prev = current;
			current = current->next;
			if( current == NULL )
			{
				printf( "current is NULL \n" );
				prev->next = anode;
				tail = anode;
			}
		}
		else
		{
			/* anode is smaller, then insert */
			printf( "anode is smaller, insert it \n" );
			if( current == head )
			{
				anode->next = head;
				head = anode;
				return 0;
			}
			/* get the next node pointer */
			prev->next = anode;
			anode->next = current;
			return 0;
		}
	}

	return 0;
#endif
#endif 

#ifdef M2
	tail->next = anode;
	tail = anode;
	printf( "tail = 0x%x \n", tail );
	return 0;
#endif

} 

/* print the whole list */
int list_print( void )
{
	lnode * current = NULL;
	int counter = 0;

	if( head == NULL )
		printf( "the list is null \n" );

	/* set current as the head of list */
	current = head;

	while( current )
	{
		printf( " %d: %s", counter, current->pline );
		counter++;
		current = current->next;
	}	

	return 0;
}
