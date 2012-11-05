#include "fsm.h"

#include "public.h"

/* define Event Type */
#define EVENT_K_NULL_DATA	""

/* server checked his name ok */

/* server checked his name reserved */

/* server checked his name exists */

enum condition
{
	E0_K_NULL = 0,
	E1_K_INPUT_USERNAME,		// 1
	E2_N_REG_NAME_OK, 		// 2
	E3_K_INPUT_PASSWORD,		// 3
	E4_K_REINPUT_PASSWORD,		// 4
	E5_PASSWORD_SAME,		// 5
	E6_N_REG_OK,			// 6

	E7_N_REG_NAME_RESERVED,		// 7
	E8_N_REG_NAME_EXISTS,		// 8
};

enum state
{
	S0_START = 0,
	S1_USER_INPUT_NAME_OK,		// 1
	S2_USER_REG_NAME_OK,		// 2
	S3_USER_INPUT_PASSWORD_OK,	// 3
	S4_USER_REINPUT_PASSWORD_OK,	// 4
	S5_USER_PASSWORD_OK,         	// 5
	S6_USER_REG_OK          	// 6
};

#if 0

state: s0
/* start state */
(data)	(event)			(condition)		(new_state)
""	EVENT_K_NULL_DATA	EVENT_K_NULL		s0	/* start */
string	EVENT_K_STRING_DATA	EVENT_K_INPUT_USERNAME	s1	/* has input username */

state: s1
/* input name ok state */
"REG_NAME_OK"		EVENT_N_REG_NAME_OK		s2	/* username check ok */
"REG_NAME_RESERVED"	EVENT_N_REG_NAME_RESERVED	s0	/* username is system reserved */
"REG_NAME_EXISTS"	EVENT_N_REG_NAME_EXISTS		s0	/* username exists already */

state: s2
/* server check name ok state */
string	EVENT_K_STRING_DATA	EVENT_K_STRING		s3	/* has input username */
"REG_OK"		EVENT_N_REG_NAME_OK		s2	/* username check ok */

#endif


