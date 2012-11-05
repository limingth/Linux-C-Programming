#include <stdlib.h>
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

/* define a transiton function pointer */
typedef int (*PF_III) ( int, int );
static PF_III _state_transition = NULL;

/* define a action function pointer */
typedef void (*PF_VV) ( void );
static PF_VV (*_transition_action) ( int, int );

typedef PF_VV (*PF_VV_II) ( int, int );

int fsm_get_state()
{
	return fsm_state;
}

int fsm_set_condition( int cond )
{
	fsm_condition = cond;
	return 0;
}

#if 0
int fsm_set_state( int state )
{
	return (fsm_state=state);
}

int fsm_get_condition()
{
	return fsm_condition;
}
#endif

int fsm_init_install( PF_III ptrans, PF_VV_II pact )
{
	_state_transition = ptrans;
	_transition_action = pact;
	return 0;
}

/* translate an event to condition */
int fsm_event_insert( int event )
{
	DPRINTF( "event:%d generated! \n", event );
		
	fsm_condition = event;
					
	return event;
}

/* check state machine transition table */
int fsm_state_transition()
{
	int new_state = 0;
	void (*action)( void );

	if( _state_transition != NULL )
		new_state = _state_transition( fsm_state, fsm_condition ); 

	DPRINTF( "state:%d ---cond:%d---> new_state:%d \n", fsm_state, fsm_condition, new_state );

	/* get user registed action pointer and call it */
	if( _transition_action != NULL )
	{
		action = (void(*)(void)) _transition_action( fsm_state, fsm_condition );
		if( action != NULL )
			action();
	}
	
	fsm_state = new_state;
	return 0; 
}

