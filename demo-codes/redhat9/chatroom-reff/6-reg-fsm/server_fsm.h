#include "fsm.h"

enum condition
{
	E0_L_NULL = 0,
	E1_L_REG_NAME_OK,	// 1
	E2_L_LOGIN_OK,		// 2

	E3_L_REG_NAME_RESERVED,	// 3
	E4_L_REG_NAME_EXIST,	// 4
	E5_L_LOGIN_NAME_ERR,	// 5
	E6_L_LOGIN_PASSWORD_ERR,	// 6
	E7_L_UPDATE_OK,			// 7	
	E8_L_LOGOUT			// 8	
};

enum state
{
	S0_START = 0,
	S1_USER_REGISTER,	// 1
	S2_USER_ONLINE,		// 2
	S3_USER_OFFLINE		// 3
};


#if 0
state: s0
/* start state */
(condition)		(new_state)
E0_L_NULL		S0_START		/* start */
E1_L_REG_NAME_OK	S1_USER_REGISTER
E2_L_LOGIN_OK		S2_USER_ONLINE		
/* not good input */
E3_N_REG_NAME_RESERVED	S0_START
E4_N_REG_NAME_EXIST	S0_START
E5_N_LOGIN_NAME_ERR	S0_START
E6_N_LOGIN_PASSWORD_ERR S0_START

state: s1:
(condition)		(new_state)
E7_N_UPDATE_OK		S2_USER_ONLINE
E?			S1_REGISTER_OK		

state: s2:
(condition)		(new_state)
E8_N_LOGOUT		S3_USER_OFFLINE	
E?			S2_USER_ONLINE		

#endif


