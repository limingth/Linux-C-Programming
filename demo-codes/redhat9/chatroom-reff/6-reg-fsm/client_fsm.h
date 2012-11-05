#include "fsm.h"

/* define Event Type */
#define D_NULL	""

/* user input "new" */
#define D_NEW	"new"

/* user input "guest" */
#define EVENT_K_GUEST_DATA 	"guest"

/* server checked his name ok */

/* server checked his name reserved */

/* server checked his name exists */

enum condition
{
	C0_K0_INPUT_NULL = 0,
	C1_N1_WELCOME,		// 1
	C2_K1_INPUT_NEW,	// 2
	C3_N2_HINT_REGISTER,	// 3
	C4_K2_INPUT_NAME,	// 4
	C5_N3_REG_NAME_OK,	// 5
	C6_K3_INPUT_INFO,	// 6
	C7_N4_UPDATE_INFO_OK	// 7
};

enum state
{
	S0_START = 0, 
	S1_WAIT_USER_CHOICE,
	S2_NEW_USER_REGISTER,	
	S3_WAIT_USER_NAME,		
	S4_WAIT_SERVER_CHECK_USER_NAME,
	S5_WAIT_USER_INFO,
	S6_WAIT_SERVER_UPDATE_USER_INFO,
	S7_CHAT
};

#if 0
state: s0
/* start state */
(condition)		(new_state)		
E1_N1_WELCOME		S1_WAIT_USER_CHOICE		

state: s1
(condition)		(new_state)
E2_K1_INPUT_NEW		S2_NEW_USER_REGISTER

state: s2
(condition)		(new_state)
E3_N2_HINT_REGISTER	S3_WAIT_USER_NAME

state: s3
(condition)		(new_state)
E4_K2_INPUT_NAME	S4_WAIT_SERVER_CHECK_USER_NAME

state: s4
(condition)		(new_state)
E5_N3_REG_NAME_OK	S5_WAIT_USER_INFO

state: s5
(condition)		(new_state)
E6_K3_INPUT_INFO	S6_WAIT_SERVER_UPDATE_USER_INFO

state: s6
(condition)		(new_state)
E7_N4_UPDATE_INFO_OK	S7_CHAT



(data)	(event)			(condition)		(new_state)
""	E_K_NULL_DATA		E0_K_NULL		s0	/* start */
"new"	E_K_NEW_DATA		E1_K_NEW		s1	/* has input "new" */
"guest"	E_K_GUEST_DATA		E2_K_GUEST		s2	/* has input "guest" */
string	E_K_OTHER_STRING	E3_K_USERNAME	s3	/* has input username */

#endif


