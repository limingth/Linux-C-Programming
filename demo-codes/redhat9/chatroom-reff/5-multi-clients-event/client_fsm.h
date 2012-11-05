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

enum condition
{
	E0_K_NULL = 0,
	E1_K_NEW,		// 1
	E2_K_GUEST,		// 2
	E3_K_STRING,		// 3
};

enum state
{
	S0_START = 0,
	S1_USER_REGISTER,	// 1
	S2_GUEST_LOGIN,		// 2
	S3_USER_LOGIN,		// 3
};

#if 0
state: s0
/* start state */
(data)	(event)			(condition)		(new_state)
""	E_K_NULL_DATA		E0_K_NULL		s0	/* start */
"new"	E_K_NEW_DATA		E1_K_NEW		s1	/* has input "new" */
"guest"	E_K_GUEST_DATA		E2_K_GUEST		s2	/* has input "guest" */
string	E_K_OTHER_STRING	E3_K_USERNAME	s3	/* has input username */

#endif


