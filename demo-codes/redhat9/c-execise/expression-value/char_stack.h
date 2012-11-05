/* 
 * char_stack.c
 * Function:		provide some stack operation for integer
 * Author:		Kong Fanbin
 * Date:		2007-04-17
 * Version:		1.0
 */
/* 
 * Function name:	push()
 *
 * Function:		push a integer into stack
 * Input:		integer a
 * Output:		none	
 * Return value:	if stack is full return ERROR,else return OK 
 */

char push_char( char a );
/* 
 * Function name:	pop()
 *
 * Function:		pop an char out of the stack
 * Input:		none	
 * Output:		char a
 * Return value:	if stack is empty return ERROR,else return the top
 * 			char of the stack.
 */

char pop_char();
/* 
 * Function name:	get_top()
 *
 * Function:		get the top byte of the stack,NOT poping it
 * Input:		none	
 * Output:		char a
 * Return value:	if stack is empty return ERROR,else return the top
 * 			of the stack
 */

char get_top_char();

