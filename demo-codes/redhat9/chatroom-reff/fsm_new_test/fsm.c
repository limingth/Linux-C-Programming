#include <stdlib.h>
#include "fsm.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<fsm> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif

typedef void (*PF_VV) ( void );
typedef int (*PF_III) ( int, int );
typedef PF_VV (*PF_VV_II) ( int, int );

/* different state-machine design as below */
#define EVENT_NUM               5       
#define STATE_NUM               5       

/* state machine transition table */
int client_fsm_transition_table[STATE_NUM][EVENT_NUM] = { 0 };

void (*client_fsm_action_table[STATE_NUM][EVENT_NUM])( void ) = { NULL }; 

extern int client_select_fd[];

/* client implement low-level functions */
int client_state_transition( int state, int cond )
{
        return client_fsm_transition_table[state][cond];
}

PF_VV client_transition_action( int state, int cond )
{
        return client_fsm_action_table[state][cond];
}

/* init fsm */
int client_fsm_init( void )
{
	int i, j;

	/* init state machine table */
	for( i = 0; i < STATE_NUM; i++ )
		for( j = 0; j < EVENT_NUM; j++ )
		{
			client_fsm_transition_table[i][j] = i;
			client_fsm_action_table[i][j] = NULL;
		}
	
	/* install fsm hooker */
	fsm_init_install( client_state_transition, client_transition_action );	

	/* state 0 -> state 0, 1, 2, 3 */
	client_fsm_transition_table[S0_START][E0_K_NULL] = S0_START;
	client_fsm_transition_table[S0_START][E1_K_NEW] = S1_USER_REGISTER;
	client_fsm_transition_table[S0_START][E2_K_GUEST] = S2_GUEST_LOGIN;
	client_fsm_transition_table[S0_START][E3_K_STRING] = S3_USER_LOGIN;
	
	client_fsm_action_table[S0_START][E0_K_NULL] = client_fsm_display_welcome;
	client_fsm_action_table[S0_START][E1_K_NEW] = client_reg_fsm;

	return 0;
}



int main( void )
{
	static FSM client_fsm;
	client_fsm._state_transition = client_state_transition;
	client_fsm._transition_action = client_transition_action;


}

int fsm_get_state()
{
	return fsm_state;
}

int fsm_set_condition( int cond )
{
	fsm_condition = cond;
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

