/* 
 * char_stack.c
 * Function:		provide some stack operation for integer
 * Author:		Kong Fanbin
 * Date:		2007-04-17
 * Version:		1.0
 */
#include <stdio.h>
#define ERROR -1
#define OK     0
#define STACK_LEN 1000

/* prepare this char array for pushing or poping */ 
static char stack[1000];

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

char push_char( char a )
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
 * Function:		pop an char out of the stack
 * Input:		none	
 * Output:		char a
 * Return value:	if stack is empty return ERROR,else return the top
 * 			char of the stack.
 */

char pop_char()
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

char get_top_char()
{
	/* if the stack is empty,return error */
	if ( i == 0 )
		return ERROR;
	else /* else return the top item  */
	{
		return stack[i-1];
	}
}

