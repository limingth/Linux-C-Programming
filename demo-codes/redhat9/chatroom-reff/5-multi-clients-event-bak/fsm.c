
#include "fsm.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<fsm> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif


/* define current condition */
static int fsm_condition = 0;

/* define current state */
static int fsm_state = 0;

extern int _state_transition( int, int );

int fsm_get_state()
{
	return fsm_state;
}

int fsm_set_state( int state )
{
	return (fsm_state=state);
}

int fsm_get_condition()
{
	return fsm_condition;
}

int fsm_set_condition( int cond )
{
	fsm_condition = cond;
	return 0;
}
/* check state machine transition table */
int fsm_state_transition()
{
	int new_state = 0;

	new_state = _state_transition( fsm_state, fsm_condition ); 

	DPRINTF( "state:%d ---cond:%d---> new_state:%d \n", fsm_state, fsm_condition, new_state );
	
	return new_state; 
}

