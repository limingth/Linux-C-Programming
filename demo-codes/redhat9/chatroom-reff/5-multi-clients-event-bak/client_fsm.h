#include "fsm.h"

/* define Event Type */
#define EVENT_K_NULL_DATA	""

/* user input "new" */
#define EVENT_K_NEW_DATA	"new"

/* user input "guest" */
#define EVENT_K_GUEST_DATA 	"guest"

/* server checked his name ok */

/* server checked his name reserved */

/* server checked his name exists */

enum 
{
	EVENT_K_NULL = 0,
	EVENT_K_NEW,		// 1
	EVENT_K_GUEST,		// 2
	EVENT_K_STRING,		// 3
	EVENT_N_REG_NAME_OK,	// 4
	EVENT_N_REG_NAME_RESERVED,	// 5
	EVENT_N_REG_NAME_EXISTS,	// 6
	EVENT_N_REG_OK			// 7	
};

enum state
{
	STATE_START = 0,
	STATE_USER_REGISTER,	// 1
	STATE_GUEST_LOGIN,	// 2
	STATE_USER_LOGIN,	// 3
	STATE_USER_REGISTER_NAME,	// 4
	STATE_USER_REGISTER_PASSWORD,	// 5
	STATE_USER_REGISTER_OK		// 6
};

#if 0
state: s0
/* start state */
(data)	(event)			(condition)		(new_state)
""	EVENT_K_NULL_DATA	EVENT_K_NULL		s0	/* start */
"new"	EVENT_K_NEW_DATA	EVENT_K_NEW		s1	/* has input "new" */
"guest"	EVENT_K_GUEST_DATA	EVENT_K_GUEST		s2	/* has input "guest" */
string	EVENT_K_STRING		EVENT_K_USERNAME	s3	/* has input username */

state: s1
/* register state */
/* register -> wait user input username */
(data)	(event)			(condition)		(new_state)
string	EVENT_K_STRING 		EVENT_K_USERNAME	s4	/* input username ok */

state: s4
/* wait server check reg name state */
/* register -> user input username -> wait server check */
(data)	(event)		(condition)			(new_state)
"REG_NAME_OK"		EVENT_N_REG_NAME_OK		s5	/* username check ok */
"REG_NAME_RESERVED"	EVENT_N_REG_NAME_RESERVED	s1	/* username is system reserved */
"REG_NAME_EXISTS"	EVENT_N_REG_NAME_EXISTS		s1	/* username exists already */

state: s5
/* wait user input password state */
/* register -> server checked user input username ok -> wait user input password */
(data)	(event)		(condition)		(new_state)
"REG_OK"		EVENT_N_REG_OK		s6	/* input password ok, reg finish! */

state: s6
/* chat start state */
(data)	(event)		(condition)		(new_state)

#endif


