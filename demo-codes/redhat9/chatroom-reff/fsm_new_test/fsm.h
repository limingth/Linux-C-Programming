

typedef int (*PF_III) ( int, int );
typedef void (*PF_VV) ( void );

typedef struct fsm
{
	int state;
	int condition;

	PF_III _state_transition;
	PF_VV (*_transition_action) ( int, int );

	void (*_set_condition)(int);
	void (*_get_state)(int);

} FSM;
