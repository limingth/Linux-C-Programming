
#define LISTEN_PORT 9000
#define SERVER_IP "127.0.0.1"

enum server_comm_packet_id_t
{
	P0_S_NULL = 0,
	P1_S_WELCOME,
	P2_S_HINT_REGISTER,
	P3_S_REG_NAME_OK,
	P4_S_UPDATE_INFO_OK
};

enum client_comm_packet_id_t
{
	P0_C_NULL = 0,
	P1_C_REG_NAME,
	P2_C_UPDATE_INFO
};

struct comm_packet_reg_t
{
	char name[32];		// 
	char passwd[32];	//
} reg_packet;
