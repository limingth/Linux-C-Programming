/* 
 * int_stack.c
 * Function:		provide some stack operation for integer
 * Author:		Kong Fanbin
 * Date:		2007-04-17
 * Version:		1.0
 */
#include <stdio.h>
#define ERROR -1
#define OK     0
#define STACK_LEN 1000

/* prepare this int array for pushing or poping */ 
static int stack[1000];

/* i is the stack top pointer */
static int i = 0;

/* 
 * Function name:	push()
 *
 * Function:		push a integer into stack
 * Input:		integer a
 * Output:		none	
 * Return value:	if stack is full return ERROR,else return OK 
 */

int push_int( int a )
{
	/* if the stack is full ,return error */
	if ( i == STACK_LEN )
		return ERROR;
	else /* else push a to stack */
	{
		stack[i] = a;
		i++;
		return OK;
	}
}

/* 
 * Function name:	pop()
 *
 * Function:		pop an integer out of the stack
 * Input:		none	
 * Output:		integer a
 * Return value:	if stack is empty return ERROR,else return the top
 * 			integer of the stack.
 */

int pop_int()
{
	/* if the stack is empty ,return error */
	if ( i == 0 )
		return ERROR;
	else /* else return the top item, and stack pointer decrease */
	{
		i--;
		return stack[i];
	}
}

/* 
 * Function name:	get_top()
 *
 * Function:		get the top byte of the stack,NOT poping it
 * Input:		none	
 * Output:		char a
 * Return value:	if stack is empty return ERROR,else return the top
 * 			of the stack
 */

int get_top_int()
{
	/* if the stack is empty,return error */
	if ( i == 0 )
		return ERROR;
	else /* else return the top item  */
	{
		return stack[i-1];
	}
}

